#pragma once

#include "MemoryLocation.h"

class Array : public MemoryLocation
{
public:
    Array(llvm::Value* value, std::string name, uint64_t size);

    virtual z3::expr createConstraint(Path* path) override;

private:
    uint64_t size;
};
