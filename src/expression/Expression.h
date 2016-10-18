#pragma once

#include <iostream>
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

    virtual void dump(int priority = 0);

private:
    llvm::Value* value;
};