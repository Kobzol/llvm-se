#pragma once

namespace llvm {
    class Instruction;
}

class Path;

class InstructionHandler
{
public:
    virtual void handle(Path* path, llvm::Instruction* instruction) = 0;
};
