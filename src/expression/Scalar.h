#pragma once

#include "MemoryLocation.h"

class Scalar : public MemoryLocation
{
public:
    Scalar(llvm::Value* value, std::string name);
    Scalar(llvm::Value* value, Expression* content, std::string name);

    virtual z3::expr createConstraint(Path* path) override;
};
