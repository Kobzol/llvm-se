#include "Path.h"

#include <llvm/IR/BasicBlock.h>

#include "instruction/InstructionDispatcher.h"
#include "solver/ExprTracker.h"
#include "state/SymbolicState.h"
#include "state/StateWrapper.h"
#include "util/Logger.h"

z3::context Path::CTX;


Path::Path(std::vector<ISymbolicState*> parentStates, PathGroup* pathGroup, llvm::Instruction* start)
    : Path(parentStates, std::make_unique<SymbolicState>(), pathGroup, start)
{

}
Path::Path(std::vector<ISymbolicState*> parentStates, std::unique_ptr<ISymbolicState> localState,
           PathGroup* pathGroup, llvm::Instruction* start)
        : instruction(start),
          pathGroup(pathGroup),
          localState(std::move(localState))
{
    parentStates.push_back(this->localState.get());
    this->state = std::make_unique<StateWrapper>(parentStates);
}

bool Path::isFinished() const
{
    return this->finished;
}
z3::context& Path::getContext()
{
    return Path::CTX;
}
StateWrapper* Path::getState() const
{
    return this->state.get();
}

PathGroup* Path::getGroup() const
{
    return this->pathGroup;
}

std::unique_ptr<Solver> Path::createSolver()
{
    return std::make_unique<Solver>(&this->getContext(), this);
}

void Path::dump(int priority)
{
    Logger::get().line(priority, "PATH %", this);
    this->getState()->dump(priority);

    Logger::get().line(priority, "Conditions");
    for (Expression* condition : this->pathConditions)
    {
        condition->dump(priority, 0);
    }

    Logger::get().line(priority, "------");
}

void Path::moveToNextInstruction()
{
    this->instruction = this->instruction->getNextNode();
}
void Path::jumpTo(llvm::Instruction* instruction)
{
    this->instruction = instruction;
}
void Path::executeInstruction()
{
    InstructionDispatcher::get().dispatch(this, this->instruction);
}
llvm::Instruction* Path::getInstruction() const
{
    return this->instruction;
}

void Path::setFinished(Expression* value)
{
    this->finished = true;
    this->returnValue = value;
}
Expression* Path::getReturnValue() const
{
    return this->returnValue;
}

void Path::addCondition(Expression* condition)
{
    this->pathConditions.push_back(condition);
}

void Path::setConditions(Solver& solver)
{
    for (Expression* exp : this->pathConditions)
    {
        solver.addConstraint(exp->createConstraint(this));
    }
}

std::unique_ptr<Path> Path::clone()
{
    std::vector<ISymbolicState*> states = this->getState()->getStates();
    states.pop_back();  // remove the local state, it's copy will be passed to the cloned path

    std::unique_ptr<Path> cloned = std::make_unique<Path>(states,
                                                          this->localState->clone(),
                                                          this->getGroup(),
                                                          this->getInstruction());

    for (Expression* exp : this->pathConditions)
    {
        cloned->pathConditions.push_back(exp);
    }

    return cloned;
}

void Path::copyTo(Path* path)
{
    ISymbolicState* local = path->getState()->getLocalState();

    // copy global updates
    for (auto& kv : this->getState()->getGlobalUpdates())
    {
        if (kv.second.getState() == local)
        {
            MemoryLocation* src = static_cast<MemoryLocation*>(local->getExpr(kv.first));
            std::unique_ptr<Expression> cloned = kv.second.getExpr()->deepClone(local);

            local->addExpr(cloned->getValue(), cloned.get());
            src->setContent(cloned.get());
            cloned.release();
        }
        else
        {
            path->getState()->storeGlobalUpdate(kv.first, kv.second.getState(), kv.second.getExpr());
        }
    }

    // copy expressions
    for (Expression* expr : this->pathConditions)
    {
        ExprTracker tracker;
        expr->markAddresses(&tracker);

        for (llvm::Value* addr : tracker.getAddresses())
        {
            if (path->getState()->hasExpr(addr))
            {
                std::unique_ptr<Expression> clonedExpr = expr->deepClone(path->getState());
                path->getState()->addExpr(addr, clonedExpr.get());
                clonedExpr.release();
            }
        }
    }
}
