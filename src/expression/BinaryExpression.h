#pragma once

#include <memory>

#include "Expression.h"

class BinaryExpression : public Expression
{
public:
    Expression* getLHS() const;
    Expression* getRHS() const;

    virtual bool isConstant() const override;

    virtual void dump(int priority) override;

protected:
    BinaryExpression(llvm::Value* value, Expression* lhs, Expression* rhs);

public:
    virtual std::unique_ptr<Expression> deepClone(ISymbolicState* state) override;

private:
    Expression* lhs;
    Expression* rhs;
};
