#pragma once

#include <vector>
#include <memory>

#include "MemoryLocation.h"

class IndexExpression : public MemoryLocation
{
public:
    IndexExpression(llvm::Value* value, MemoryLocation* base, int64_t index);
    IndexExpression(llvm::Value* value, MemoryLocation* base, std::vector<std::shared_ptr<Expression>> indices);

    virtual z3::expr createConstraint(Path* path) override;
    virtual const std::string& getIdentifier() const override;

    virtual void setContent(Expression* expression) override;

private:
    int64_t index = -1;
    MemoryLocation* base;
    std::vector<std::shared_ptr<Expression>> indices;
};