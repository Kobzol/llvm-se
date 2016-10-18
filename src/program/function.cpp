#include "function.h"

#include <llvm/IR/Function.h>

Function::Function(llvm::Function* handle): handle(handle)
{
    for (auto& arg: handle->getArgumentList())
    {
        this->parameters.emplace_back(arg.getName().str(), arg.getType());
    }

    auto path = std::make_unique<Path>();
    /*for (const Declaration& par : parameters) TODO
    {
        path->addVariable(par.getName(), par.getType());
    }*/

    this->paths.push_back(std::move(path));
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
Path* Function::getActivePath() const
{
    return this->paths.at(this->activePath).get();
}
