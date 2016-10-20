#pragma once

#include "InstructionHandler.h"

#include <llvm/IR/Instructions.h>

class GetElementPtr : public InstructionHandler
{
public:
    virtual void handle(Path* path, llvm::Instruction* instruction) override;

private:
    bool getConstantIndex(llvm::GetElementPtrInst* gep, int64_t* result);
};