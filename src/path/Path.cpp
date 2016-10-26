#include <instruction/InstructionDispatcher.h>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instruction.h>

#include "SymbolicState.h"
#include "WrapperState.h"
#include "Path.h"

z3::context Path::CTX;

Path::Path(ISymbolicState* parentState, PathGroup* pathGroup, llvm::Instruction* start)
    : instruction(start), pathGroup(pathGroup)
{
    this->localState = std::make_unique<SymbolicState>();
    this->state = std::make_unique<WrapperState>(this->localState.get(), parentState);
}

bool Path::isFinished() const
{
    return this->finished;
}
z3::context& Path::getContext()
{
    return Path::CTX;
}
ISymbolicState* Path::getState() const
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
    this->state->dump(priority);
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
    std::unique_ptr<Path> cloned = std::make_unique<Path>(this->state.get(), this->getGroup(), this->getInstruction());

    for (Expression* exp : this->pathConditions)
    {
        cloned->pathConditions.push_back(exp);
    }

    return cloned;
}
