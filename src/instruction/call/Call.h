#pragma once

#include <memory>
#include <vector>

#include "instruction/InstructionHandler.h"
#include "CallHandler.h"

class Call : public InstructionHandler
{
public:
    Call();

    virtual void handle(Path* path, llvm::Instruction* instruction) override;

private:
    std::vector<std::unique_ptr<CallHandler>> handlers;
};
