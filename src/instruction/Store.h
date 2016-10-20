#pragma once

#include "InstructionHandler.h"

class Store : public InstructionHandler
{
public:
    virtual void handle(Path* path, llvm::Instruction *instruction) override;
};