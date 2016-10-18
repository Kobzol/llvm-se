#pragma once

#include "Expression.h"

class UnknownExpression : public Expression
{
public:
    UnknownExpression(llvm::Value* value);

    virtual void dump(int priority) override;

    virtual z3::expr createConstraint(Path* path) override;
};