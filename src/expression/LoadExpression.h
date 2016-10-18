#pragma once

#include "Expression.h"

class LoadExpression : public Expression
{
public:
    LoadExpression(llvm::Value* value, Expression* source);

    Expression* getSource() const;

    virtual void dump(int priority) override;

    virtual z3::expr createConstraint(Path* path) override;

private:
    Expression* source;
};