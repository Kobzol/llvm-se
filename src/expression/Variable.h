#pragma once

#include "MemoryLocation.h"

class Variable : public MemoryLocation
{
public:
    Variable(llvm::Value* value, uint64_t count);
    Variable(llvm::Value* value, uint64_t count, Expression* content);

    virtual z3::expr createConstraint(Path* path) override;
};