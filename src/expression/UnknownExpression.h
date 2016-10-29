#pragma once

#include "Expression.h"

class UnknownExpression : public Expression
{
public:
    UnknownExpression(llvm::Value* value);

    virtual void dump(int priority = 0, int indent = 0) override;

    virtual bool isUnknown() const override;

    virtual z3::expr createConstraint(Path* path) override;

    virtual std::unique_ptr<Expression> deepClone(ISymbolicState* state) override;
};