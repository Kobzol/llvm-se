#pragma once

#include "ISymbolicState.h"

class Path;

class WrapperState : public ISymbolicState
{
public:
    WrapperState(ISymbolicState* primary, ISymbolicState* secondary);

    virtual bool hasExpr(llvm::Value* address) const override;
    virtual Expression* getExpr(llvm::Value* address) const override;
    virtual void addExpr(llvm::Value* address, Expression* expression) override;

    virtual void setConstraints(Path* path, Solver& solver) const override;

    virtual void dump(int priority) override;

private:
    ISymbolicState* primary;
    ISymbolicState* secondary;
};
