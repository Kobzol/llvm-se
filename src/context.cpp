#include "context.h"

#include <llvm/IR/Module.h>

Context::Context()
{
    this->analyser = std::make_unique<Analyser>(this);
}

llvm::Module* Context::getActiveModule() const
{
    return this->activeModule;
}
void Context::handleModule(llvm::Module* module)
{
    this->activeModule = module;
    module->dump();

    for (auto& fn : module->getFunctionList())
    {
        std::vector<Declaration> params;
        for (auto& arg: fn.getArgumentList())
        {
            params.emplace_back(arg.getName().str(), arg.getType());
        }
        this->functions.push_back(std::make_unique<Function>(&fn));
    }

    // TODO: topological sort
    for (auto& fn : this->functions)
    {
        this->analyser->analyseFunction(fn.get());
    }
}

Function* Context::getFunctionByName(std::string name) const
{
    for (auto& fn : this->functions)
    {
        if (fn->getName() == name) return fn.get();
    }

    return nullptr;
}
