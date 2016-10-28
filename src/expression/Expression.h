#pragma once

#include <memory>

#include <z3++.h>

namespace llvm {
    class Value;
    class Type;
}

class Path;

class Expression
{
public:
    Expression(llvm::Value* value);

    llvm::Value* getValue() const;
    llvm::Type* getType() const;

    virtual z3::expr createConstraint(Path* path) = 0;

    virtual bool isConstant() const;
    virtual bool isMemoryLocation() const;
    virtual bool isLoad() const;
    virtual bool isUnknown() const;

    virtual std::unique_ptr<Expression> clone();

    virtual void dump(int priority = 0);

private:
    llvm::Value* value;
};