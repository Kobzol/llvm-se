#pragma once

#include "Expression.h"

class MemoryLocation;

class LoadExpression : public Expression
{
public:
    LoadExpression(llvm::Value* value, MemoryLocation* source);

    MemoryLocation* getSource() const;

    virtual void dump(int priority) override;

    virtual z3::expr createConstraint(Path* path) override;

private:
    MemoryLocation* source;
};