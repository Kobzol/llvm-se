#pragma once

#include "ISymbolicState.h"

class WrapperState : public ISymbolicState
{
public:
    WrapperState(ISymbolicState* primary, ISymbolicState* secondary);

    virtual bool hasMemoryLoc(llvm::Value* address) const override;
    virtual MemoryLocation* getMemoryLoc(llvm::Value* address) const override;
    virtual void addMemoryLoc(llvm::Value* address, MemoryLocation* memoryLocation) override;

    virtual bool hasExpr(llvm::Value* address) const override;
    virtual Expression* getExpr(llvm::Value* address) const override;
    virtual void addExpr(llvm::Value* address, Expression* expression) override;

    virtual void dump(int priority) override;

private:
    ISymbolicState* primary;
    ISymbolicState* secondary;
};
