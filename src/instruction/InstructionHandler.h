#pragma once

namespace llvm {
    class Instruction;
}

class Function;

class InstructionHandler
{
public:
    virtual void handle(Function* function, llvm::Instruction* instruction) = 0;
};