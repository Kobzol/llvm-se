#pragma once

#include <vector>
#include <memory>

#include "instruction/InstructionHandler.h"

namespace llvm {
    class BasicBlock;
    class Instruction;
}

class Context;
class Function;

class Analyser
{
public:
    Analyser(Context* context);

    void analyseFunction(Function* function);

private:
    void analyseBlock(llvm::BasicBlock& block);
    void analyseInstruction(llvm::Instruction& instruction);

    std::unique_ptr<InstructionHandler> handlers[256];
    Context* context;
    Function* activeFunction;
    llvm::BasicBlock* activeBlock;
};
