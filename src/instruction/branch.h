#pragma once

#include "InstructionHandler.h"

class Branch : public InstructionHandler
{
public:
    virtual void handle(Function* function, llvm::Instruction* instruction) override;
};
