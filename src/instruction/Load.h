#pragma once

#include "InstructionHandler.h"

class Load : public InstructionHandler
{
public:
    virtual void handle(Path* path, llvm::Instruction* instruction) override;
};
