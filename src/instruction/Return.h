#pragma once

#include "InstructionHandler.h"

class Return : public InstructionHandler
{
public:
    virtual void handle(Path* path, llvm::Instruction* instruction) override;
};
