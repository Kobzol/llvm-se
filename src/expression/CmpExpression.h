#pragma once

#include <llvm/IR/InstrTypes.h>

#include "BinaryExpression.h"

class CmpExpression : public BinaryExpression
{
public:
    CmpExpression(llvm::Value* value, Expression* lhs, Expression* rhs, llvm::CmpInst::Predicate predicate);

    virtual void dump(int priority = 0, int indent = 0) override;

    virtual z3::expr createConstraint(Path* path) override;

    virtual std::unique_ptr<Expression> deepClone(ISymbolicState* state) override;

private:
    llvm::CmpInst::Predicate predicate;
};
