#pragma once

#include <memory>

#include "util/Singleton.h"
#include "InstructionHandler.h"

class InstructionDispatcher : public Singleton<InstructionDispatcher>
{
    friend class Singleton<InstructionDispatcher>;

public:
    void dispatch(Path* path, llvm::Instruction* instruction);

protected:
    InstructionDispatcher();

private:
    std::unique_ptr<InstructionHandler> handlers[256];
};
