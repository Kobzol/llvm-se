#pragma once

#include "InstructionHandler.h"

class Store : public InstructionHandler
{
public:
    virtual void handle(Function *function, llvm::Instruction *instruction) override;
};