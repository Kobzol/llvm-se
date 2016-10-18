#pragma once

#include <memory>

#include "Expression.h"

class BinaryExpression : public Expression
{
public:
    BinaryExpression(llvm::Value* value, Expression* lhs, Expression* rhs);

    Expression* getLHS() const;
    Expression* getRHS() const;

    virtual void dump(int priority) override;

private:
    Expression* lhs;
    Expression* rhs;
};
