#pragma once

#include "InstructionHandler.h"

class Branch : public InstructionHandler
{
public:
    virtual void handle(Path* path, llvm::Instruction* instruction) override;
};
