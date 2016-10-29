#pragma once

namespace llvm {
    class Instruction;
}

class Path;

class InstructionHandler
{
public:
    virtual ~InstructionHandler();

    virtual void handle(Path* path, llvm::Instruction* instruction) = 0;
};
