#pragma once

#include "ISymbolicState.h"

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <memory>

#include "expression/Expression.h"
#include "expression/MemoryLocation.h"

class Path;

class SymbolicState : public ISymbolicState
{
public:
    virtual bool hasExpr(llvm::Value* address) const override;
    virtual Expression* getExpr(llvm::Value* address) const override;
    virtual void addExpr(llvm::Value* address, Expression* expression) override;

    virtual std::unique_ptr<Expression> copyExpr(llvm::Value* address) override;

    virtual void setConstraints(Path* path, Solver& solver) const override;

    virtual void dump(int priority) override;

private:
    void store(llvm::Value* address, Expression* expression);

    std::unordered_map<llvm::Value*, Expression*> expressions;
    std::unordered_set<Expression*> memoryMap;
    std::vector<std::unique_ptr<Expression>> memory;
};