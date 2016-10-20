#include "Context.h"

#include <llvm/IR/Module.h>
#include <llvm/IR/IntrinsicInst.h>
#include <llvm/IR/DebugInfoMetadata.h>

#include "util/DebugUtil.h"
#include "expression/ExprBuilder.h"
#include "path/PathGroup.h"


llvm::Module* Context::getActiveModule() const
{
    return this->activeModule;
}
void Context::handleModule(llvm::Module* module)
{
    this->activeModule = module;

    for (auto& fn : module->getFunctionList())
    {
        std::vector<Declaration> params;
        for (auto& arg: fn.getArgumentList())
        {
            params.emplace_back(arg.getName().str(), arg.getType());
        }
        this->functions.push_back(std::make_unique<Function>(&fn));
    }

    std::unique_ptr<SymbolicState> state = this->createGlobalState(module);
    Function* main = this->getFunctionByName("main");
    assert(main);

    PathGroup pathGroup;
    std::unique_ptr<Path> mainPath = std::make_unique<Path>(state.get(), main, &pathGroup);
    pathGroup.addPath(std::move(mainPath));
    pathGroup.exhaust();
}

Function* Context::getFunctionByName(std::string name) const
{
    for (auto& fn : this->functions)
    {
        if (fn->getName() == name)
        {
            return fn.get();
        }
    }

    return nullptr;
}

std::unique_ptr<SymbolicState> Context::createGlobalState(llvm::Module* module)
{
    std::unique_ptr<SymbolicState> state = std::make_unique<SymbolicState>();
    ExprBuilder builder(state.get());

    for (llvm::GlobalVariable& global : module->getGlobalList())
    {
        state->addMemoryLoc(&global, static_cast<MemoryLocation*>(builder.build(&global)));
    }

    return state;
}
