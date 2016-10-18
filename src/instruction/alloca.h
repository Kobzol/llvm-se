#pragma once

#include "InstructionHandler.h"

class Alloca : public InstructionHandler
{
public:
    virtual void handle(Function* function, llvm::Instruction* instruction) override;
};