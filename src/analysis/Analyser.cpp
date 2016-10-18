#include "Analyser.h"

#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/ValueSymbolTable.h>

#include "instruction/alloca.h"
#include "instruction/branch.h"
#include "instruction/GetElementPtr.h"
#include "instruction/store.h"
#include "program/function.h"
#include "util/logger.h"

Analyser::Analyser(Context* context): context(context)
{
    this->handlers[llvm::Instruction::Store] = std::make_unique<Store>();
    this->handlers[llvm::Instruction::Alloca] = std::make_unique<Alloca>();
    this->handlers[llvm::Instruction::GetElementPtr] = std::make_unique<GetElementPtr>();
    this->handlers[llvm::Instruction::Br] = std::make_unique<Branch>();

    Logger::get().setPriority(Logger::Prio::INFO);
}

void Analyser::analyseFunction(Function* function)
{
    function->getHandle()->dump();
    this->activeFunction = function;
    for (auto& block : function->getHandle()->getBasicBlockList())
    {
        this->analyseBlock(block);
    }
    //function->getActivePath()->dump();
}

void Analyser::analyseBlock(llvm::BasicBlock& block)
{
    this->activeBlock = &block;
    for (auto& inst : block.getInstList())
    {
        this->analyseInstruction(inst);
    }
}

void Analyser::analyseInstruction(llvm::Instruction& instruction)
{
    unsigned int opcode = instruction.getOpcode();
    if (opcode < 256 && this->handlers[opcode])
    {
        this->handlers[opcode]->handle(this->activeFunction, &instruction);
    }
}
