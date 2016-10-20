#include "InstructionDispatcher.h"

#include <llvm/IR/Instruction.h>

#include "Store.h"
#include "Alloca.h"
#include "GetElementPtr.h"
#include "Branch.h"

InstructionDispatcher::InstructionDispatcher()
{
    this->handlers[llvm::Instruction::Store] = std::make_unique<Store>();
    this->handlers[llvm::Instruction::Alloca] = std::make_unique<Alloca>();
    this->handlers[llvm::Instruction::GetElementPtr] = std::make_unique<GetElementPtr>();
    this->handlers[llvm::Instruction::Br] = std::make_unique<Branch>();
}

void InstructionDispatcher::dispatch(Path* path, llvm::Instruction* instruction)
{
    unsigned int opcode = instruction->getOpcode();
    if (opcode < 256 && this->handlers[opcode])
    {
        this->handlers[opcode]->handle(path, instruction);
    }
}