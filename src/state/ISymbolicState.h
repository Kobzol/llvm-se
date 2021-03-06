#pragma once

#include <memory>

#include "expression/Expression.h"

namespace llvm {
    class Value;
}

class MemoryLocation;
class Path;
class Solver;

class ISymbolicState
{
public:
    virtual ~ISymbolicState();

    virtual bool hasExpr(llvm::Value* address) const = 0;
    virtual Expression* getExpr(llvm::Value* address) const = 0;
    virtual void addExpr(llvm::Value* address, Expression* expression) = 0;

    virtual std::unique_ptr<ISymbolicState> clone() = 0;

    virtual void dump(int priority) = 0;
};
