#include "WrapperState.h"

WrapperState::WrapperState(ISymbolicState* primary, ISymbolicState* secondary)
    : primary(primary), secondary(secondary)
{

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
    this->primary->dump(priority);
    this->secondary->dump(priority);
}

void WrapperState::setConstraints(Path* path, Solver& solver) const
{
    this->primary->setConstraints(path, solver);
    this->secondary->setConstraints(path, solver);
}

std::unique_ptr<Expression> WrapperState::copyExpr(llvm::Value* address)
{
    if (this->primary->hasExpr(address))
    {
        return this->primary->copyExpr(address);
    }
    else if (this->secondary->hasExpr(address))
    {
        return this->secondary->copyExpr(address);
    }
}
