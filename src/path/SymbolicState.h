#pragma once

#include "ISymbolicState.h"

#include <unordered_map>
#include <memory>

#include "expression/Expression.h"
#include "expression/MemoryLocation.h"

class Path;

class SymbolicState : public ISymbolicState
{
public:
    virtual void store(llvm::Value* address, Expression* expression) override;

    virtual bool hasMemoryLoc(llvm::Value* address) const override;
    virtual MemoryLocation* getMemoryLoc(llvm::Value* address) const override;
    virtual void addMemoryLoc(llvm::Value* address, MemoryLocation* memoryLocation) override;

    virtual bool hasExpr(llvm::Value* address) const override;
    virtual Expression* getExpr(llvm::Value* address) const override;
    virtual void addExpr(llvm::Value* address, Expression* expression) override;

    virtual void setConstraints(Path* path, Solver& solver) const override;

    virtual void dump(int priority) override;

private:
    std::unordered_map<llvm::Value*, MemoryLocation*> memoryLocations;
    std::unordered_map<llvm::Value*, Expression*> expressions;

    std::unordered_map<llvm::Value*, std::unique_ptr<Expression>> memory;
};