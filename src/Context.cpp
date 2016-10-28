#include "Context.h"

#include <cxxabi.h>

#include <llvm/IR/Module.h>
#include <llvm/IR/IntrinsicInst.h>
#include <llvm/IR/DebugInfoMetadata.h>

#include "util/DebugUtil.h"
#include "util/Logger.h"
#include "expression/ExprBuilder.h"
#include "path/PathGroup.h"


llvm::Module* Context::getActiveModule() const
{
    return this->activeModule;
}
void Context::handleModule(llvm::Module* module)
{
    this->activeModule = module;

    //Logger::get().setPriority(Logger::Prio::INFO);

    for (auto& fn : module->getFunctionList())
    {
        std::vector<Declaration> params;
        for (auto& arg: fn.getArgumentList())
        {
            params.emplace_back(arg.getName(), arg.getType());
        }
        this->functions.push_back(std::make_unique<Function>(&fn));
    }

    Function* main = this->getFunctionByName("main");

    if (!main)
    {
        return;
    }

    main->getHandle()->dump();

    PathGroup pathGroup(this);
    std::unique_ptr<SymbolicState> state = this->createGlobalState(module);
    std::unique_ptr<Path> mainPath = std::make_unique<Path>(std::vector<ISymbolicState*>{ state.get() },
                                                              &pathGroup,
                                                              main->getFirstInstruction());
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
        state->addExpr(&global, static_cast<MemoryLocation*>(builder.build(&global)));
    }

    return state;
}

Function* Context::getFunctionByDemangledName(std::string name) const
{
    for (auto& fn : this->functions)
    {
        std::string demangled = this->demangle(fn->getName());

        if (demangled == "") continue;

        demangled = demangled.substr(0, demangled.find("("));

        if (demangled == name)
        {
            return fn.get();
        }
    }

    return nullptr;
}

std::string Context::demangle(std::string name) const
{
    std::unique_ptr<char, void(*)(void*)> demangled = std::unique_ptr<char, void(*)(void*)>(
            abi::__cxa_demangle(name.c_str(), NULL, NULL, NULL),
            std::free
    );

    if (!demangled.get()) return "";

    size_t count = std::strlen(demangled.get());
    return std::string(demangled.get(), count);
}

void Context::keepModule(std::unique_ptr<llvm::Module> module)
{
    this->storedModules.push_back(std::move(module));
}

const std::vector<CheckError>& Context::getErrors() const
{
    return this->errors;
}

void Context::addError(CheckError error)
{
    this->errors.push_back(error);
}
