#include <instruction/InstructionDispatcher.h>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instruction.h>

#include "SymbolicState.h"
#include "WrapperState.h"
#include "Path.h"

z3::context Path::CTX;

Path::Path(ISymbolicState* parentState, Function* function, PathGroup* pathGroup)
    : Path(parentState, function, pathGroup, function->getFirstInstruction())
{

}

Path::Path(ISymbolicState* parentState, Function* function, PathGroup* pathGroup, llvm::Instruction* start)
    : function(function), instruction(start), pathGroup(pathGroup)
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
const llvm::Instruction* Path::getInstruction() const
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
