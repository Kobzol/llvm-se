#pragma once

#include "BinaryExpression.h"

class AddExpression : public BinaryExpression
{
public:
    AddExpression(llvm::Value* value, Expression* lhs, Expression* rhs);

    virtual z3::expr createConstraint(Path* path) override;

    virtual void dump(int priority) override;
};
