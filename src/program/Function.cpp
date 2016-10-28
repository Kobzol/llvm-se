#include "Function.h"

#include <llvm/IR/Function.h>

Function::Function(llvm::Function* handle): handle(handle)
{
    for (auto& arg: handle->getArgumentList())
    {
        this->parameters.emplace_back(arg.getName().str(), arg.getType());
    }
}

llvm::Function* Function::getHandle() const
{
    return this->handle;
}
std::string Function::getName() const
{
    return this->handle->getName().str();
}
llvm::Type* Function::getReturnType() const
{
    return this->handle->getReturnType();
}
const std::vector<Declaration>& Function::getParameters() const
{
    return this->parameters;
}

bool Function::isUser() const
{
    return this->getName().find("llvm.") == std::string::npos;
}

llvm::Instruction* Function::getFirstInstruction()
{
    for (llvm::BasicBlock& bb : this->getHandle()->getBasicBlockList())
    {
        for (llvm::Instruction& inst : bb.getInstList())
        {
            return &inst;
        }
    }

    assert(0);
    return nullptr;
}
