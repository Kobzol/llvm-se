#pragma once

#include <memory>

#include <z3++.h>

namespace llvm {
    class Value;
    class Type;
}

class ExprTracker;
class Path;
class ISymbolicState;

class Expression
{
public:
    Expression(llvm::Value* value);
    virtual ~Expression();

    llvm::Value* getValue() const;
    llvm::Type* getType() const;

    virtual z3::expr createConstraint(Path* path) = 0;

    virtual bool isConstant() const;
    virtual bool isMemoryLocation() const;
    virtual bool isLoad() const;
    virtual bool isUnknown() const;

    virtual std::unique_ptr<Expression> clone();
    virtual std::unique_ptr<Expression> deepClone(ISymbolicState* state);

    virtual void dump(int priority = 0, int indent = 0);

    virtual void markAddresses(ExprTracker* tracker) const;

private:
    llvm::Value* value;
};