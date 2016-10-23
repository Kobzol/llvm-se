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
    for (auto& kv : this->memoryLocations)
    {
        kv.second->dump(priority);
        Logger::get().log(priority, " = ");
        if (kv.second->getContent() != nullptr)
        {
            kv.second->getContent()->dump(priority);
        }
        else Logger::get().line(priority, "null");
    }
    for (auto& kv : this->expressions)
    {
        kv.second->dump(priority);
    }
}

void SymbolicState::setConstraints(Path* path, Solver& solver) const
{
    for (auto& kv : this->memoryLocations)
    {
        z3::expr var = kv.second->createConstraint(path);
        z3::expr value = kv.second->getContent()->createConstraint(path);
        solver.addConstraint(var == value);
    }
}

void SymbolicState::store(llvm::Value* address, Expression* expression)
{
    if (this->memory.count(address)) return;
    this->memory[address] = std::unique_ptr<Expression>(expression);
}
