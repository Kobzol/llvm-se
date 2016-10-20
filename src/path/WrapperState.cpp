#include "WrapperState.h"

#include "util/Logger.h"

WrapperState::WrapperState(ISymbolicState* primary, ISymbolicState* secondary)
    : primary(primary), secondary(secondary)
{

}

bool WrapperState::hasMemoryLoc(llvm::Value* address) const
{
    return this->primary->hasMemoryLoc(address) || this->secondary->hasMemoryLoc(address);
}
MemoryLocation* WrapperState::getMemoryLoc(llvm::Value* address) const
{
    if (this->primary->hasMemoryLoc(address))
    {
        return this->primary->getMemoryLoc(address);
    }
    else return this->secondary->getMemoryLoc(address);
}

void WrapperState::addMemoryLoc(llvm::Value* address, MemoryLocation* memoryLocation)
{
    return this->primary->addMemoryLoc(address, memoryLocation);
}

bool WrapperState::hasExpr(llvm::Value* address) const
{
    return this->primary->hasExpr(address) || this->secondary->hasExpr(address);
}
Expression* WrapperState::getExpr(llvm::Value* address) const
{
    if (this->primary->hasExpr(address))
    {
        return this->primary->getExpr(address);
    }
    else return this->secondary->getExpr(address);
}
void WrapperState::addExpr(llvm::Value* address, Expression* expression)
{
    this->primary->addExpr(address, expression);
}

void WrapperState::dump(int priority)
{
    Logger::get().line(priority, "Wrapper state");
    this->primary->dump(priority);
    this->secondary->dump(priority);
}
