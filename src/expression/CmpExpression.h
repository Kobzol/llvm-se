#pragma once

#include <llvm/IR/InstrTypes.h>

#include "BinaryExpression.h"

class CmpExpression : public BinaryExpression
{
public:
    CmpExpression(llvm::Value* value, Expression* lhs, Expression* rhs, llvm::CmpInst::Predicate predicate);

    virtual void dump(int priority) override;

    virtual z3::expr createConstraint(Path* path) override;

private:
    llvm::CmpInst::Predicate predicate;
};
