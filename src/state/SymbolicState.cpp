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
        kv.second->dump(priority, 0);
    }
}

void SymbolicState::store(llvm::Value* address, Expression* expression)
{
    if (this->memoryMap.count(expression)) return;
    this->memoryMap.insert(expression);
    this->memory.emplace_back(expression);
}

std::unique_ptr<ISymbolicState> SymbolicState::clone()
{
    std::unique_ptr<ISymbolicState> clone = std::make_unique<SymbolicState>();

    for (auto& kv : this->expressions)
    {
        Expression* expr = kv.second;
        std::unique_ptr<Expression> clonedExpr = expr->deepClone(clone.get());
        clone->addExpr(kv.first, clonedExpr.get());
        clonedExpr.release();
    }

    return clone;
}
