#include <instruction/InstructionDispatcher.h>

#include <llvm/IR/BasicBlock.h>
#include <util/Logger.h>

#include "state/SymbolicState.h"
#include "state/StateWrapper.h"
#include "Path.h"

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
    this->getState()->dump(priority);
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
    states.pop_back();  // remove the local state, which will be copied

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

void Path::mergeGlobalsTo(Path* path)
{
    // TODO: release the std::unique_ptrs in this path when merging with the given path!!!
    ISymbolicState* local = path->getState()->getLocalState();

    for (auto& kv : this->getState()->getGlobalUpdates())
    {
        if (kv.second.getState() == local)
        {
            MemoryLocation* src = static_cast<MemoryLocation*>(local->getExpr(kv.first));
            src->setContent(kv.second.getExpr());
        }
        else
        {
            path->getState()->storeGlobalUpdate(kv.first, kv.second.getState(), kv.second.getExpr());
        }
    }
}
