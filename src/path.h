#pragma once

#include <cassert>
#include <memory>
#include <map>
#include <expression/IndexExpression.h>

#include "expression/Expression.h"
#include "expression/MemoryLocation.h"
#include "solver/solver.h"

namespace llvm {
    class Value;
}

class Path
{
public:
    Path();

    void storeIntoAlloc(llvm::Value* addr, Expression* expr);
    void addAlloc(std::shared_ptr<MemoryLocation> var);
    bool hasAlloc(llvm::Value* addr) const;
    Expression* getAlloc(llvm::Value* addr) const;

    void addExpr(llvm::Value* addr, Expression* expr);
    bool hasExpr(llvm::Value* addr) const;
    Expression* getExpr(llvm::Value* addr) const;

    void dump(int priority);

    std::unique_ptr<Solver> createSolver();

    z3::context& getContext();

    void setIndexer(std::shared_ptr<IndexExpression> index);

private:
    static z3::context CTX;

    std::map<llvm::Value*, std::shared_ptr<MemoryLocation>> variables;
    std::map<llvm::Value*, std::shared_ptr<Expression>> exprs;
    std::map<llvm::Value*, std::shared_ptr<Expression>> indices;
};
