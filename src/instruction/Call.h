#pragma once

#include "InstructionHandler.h"

class Call : public InstructionHandler
{
public:
    virtual void handle(Path* path, llvm::Instruction* instruction) override;
};
