#pragma once

#include <memory>

#include "Expression.h"

class BinaryExpression : public Expression
{
public:
    Expression* getLHS() const;
    Expression* getRHS() const;

    virtual bool isConstant() const override;

    virtual void dump(int priority = 0, int indent = 0) override;

    virtual void markAddresses(ExprTracker* tracker) const override;

protected:
    BinaryExpression(llvm::Value* value, Expression* lhs, Expression* rhs);

public:
    virtual std::unique_ptr<Expression> deepClone(ISymbolicState* state) override;

private:
    Expression* lhs;
    Expression* rhs;
};
