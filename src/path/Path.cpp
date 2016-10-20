#include <instruction/InstructionDispatcher.h>
#include "Path.h"

#include "SymbolicState.h"
#include "WrapperState.h"

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
    std::unique_ptr<Solver> solver = std::make_unique<Solver>(&this->getContext());

    /*for (auto& var : this->variables) TODO
    {
        if (!var.second->isUndefined() && var.second->hasIdentifier())
        {
            z3::expr varName = var.second->createConstraint(this);
            z3::expr varValue = var.second->getContent()->createConstraint(this);
            solver->addConstraint(varName == varValue);
        }
    }*/

    return solver;
}

void Path::dump(int priority)
{
    this->state->dump(priority);
}

llvm::Instruction* Path::advance()
{
    InstructionDispatcher::get();
    return nullptr;
}
