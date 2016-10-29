#pragma once

#include <cstdint>

#include "Expression.h"

class IntConstant : public Expression
{
public:
    IntConstant(llvm::Value* value, int64_t constant);

    virtual void dump(int priotity) override;

    int64_t getConstant() const;

    virtual z3::expr createConstraint(Path* path) override;
    virtual bool isConstant() const override;

    virtual std::unique_ptr<Expression> deepClone(ISymbolicState* state) override;

private:
    int64_t constant;
};
