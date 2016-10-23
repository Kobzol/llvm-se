#include "SymbolicState.h"

#include "solver/Solver.h"
#include "util/Logger.h"

bool SymbolicState::hasExpr(llvm::Value* address) const
{
    return this->expressions.count(address) != 0;
}
Expression* SymbolicState::getExpr(llvm::Value* address) const
{
    assert(this->hasExpr(address));
    return this->expressions.at(address);
}
void SymbolicState::addExpr(llvm::Value* address, Expression* expression)
{
    this->store(address, expression);
    this->expressions[address] = expression;
}

void SymbolicState::dump(int priority)
{
    for (auto& kv : this->expressions)
    {
        kv.second->dump(priority);
    }
}

void SymbolicState::setConstraints(Path* path, Solver& solver) const
{
    for (auto& kv : this->expressions)
    {
        if (kv.second->isMemoryLocation())
        {
            solver.addMemLoc(static_cast<MemoryLocation*>(kv.second));
        }
    }
}

void SymbolicState::store(llvm::Value* address, Expression* expression)
{
    if (this->memory.count(address)) return;
    this->memory[address] = std::unique_ptr<Expression>(expression);
}
