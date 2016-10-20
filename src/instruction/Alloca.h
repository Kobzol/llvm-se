#pragma once

#include "InstructionHandler.h"

class Alloca : public InstructionHandler
{
public:
    virtual void handle(Path* path, llvm::Instruction* instruction) override;
};