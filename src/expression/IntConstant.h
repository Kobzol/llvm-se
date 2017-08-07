#pragma once

#include <cstdint>

#include "Expression.h"

class IntConstant : public Expression
{
public:
    IntConstant(llvm::Value* value, int64_t constant, size_t size);

    virtual void dump(int priority = 0, int indent = 0) override;

    virtual bool isConstant() const override;
    int64_t getConstant() const;

    virtual z3::expr createConstraint(Path* path) override;

    virtual std::unique_ptr<Expression> deepClone(ISymbolicState* state) override;

private:
    int64_t constant;
    size_t size;
};
