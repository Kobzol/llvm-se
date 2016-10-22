#pragma once

#include "InstructionHandler.h"

namespace llvm {
    class BasicBlock;
    class Instruction;
}

class Branch : public InstructionHandler
{
public:
    virtual void handle(Path* path, llvm::Instruction* instruction) override;

private:
    llvm::Instruction* getFirstInstruction(llvm::BasicBlock* block);
};
