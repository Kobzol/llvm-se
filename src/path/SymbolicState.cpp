#include "SymbolicState.h"

#include "util/Logger.h"

bool SymbolicState::hasMemoryLoc(llvm::Value* address) const
{
    return this->memoryLocations.count(address) != 0;
}
MemoryLocation* SymbolicState::getMemoryLoc(llvm::Value* address) const
{
    assert(this->hasMemoryLoc(address));
    return this->memoryLocations.at(address);
}
void SymbolicState::addMemoryLoc(llvm::Value* address, MemoryLocation* memoryLocation)
{
    this->memory[address] = std::unique_ptr<Expression>(static_cast<Expression*>(memoryLocation));
    this->memoryLocations[address] = memoryLocation;
}

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
    this->memory[address] = std::unique_ptr<Expression>(expression);
    this->expressions[address] = expression;
}

void SymbolicState::dump(int priority)
{
    Logger::get().line(priority, "Symbolic state");
}
