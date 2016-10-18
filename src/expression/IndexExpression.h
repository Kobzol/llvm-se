#pragma once

#include <vector>
#include <memory>

#include "Expression.h"

class IndexExpression : public Expression
{
public:
    IndexExpression(llvm::Value* value, const llvm::Value* pointer, int64_t index);
    IndexExpression(llvm::Value* value, const llvm::Value* pointer, std::vector<std::shared_ptr<Expression>> indices);

    virtual z3::expr createConstraint(Path* path) override;

private:
    int64_t index = -1;
    const llvm::Value* pointer;
    std::vector<std::shared_ptr<Expression>> indices;
};