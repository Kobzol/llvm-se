#pragma once

#include <cstdint>

#include "Expression.h"

class IntConstant : public Expression
{
public:
    IntConstant(llvm::Value* value, int64_t constant);

    virtual void dump(int priotity) override;

    virtual z3::expr createConstraint(Path* path) override;

private:
    int64_t constant;
};
