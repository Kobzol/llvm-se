#pragma once

#include <memory>
#include <vector>

#include <llvm/IR/Module.h>

#include "path/SymbolicState.h"
#include "program/Function.h"

class Context
{
public:
    llvm::Module* getActiveModule() const;
    void handleModule(llvm::Module* module);

    Function* getFunctionByName(std::string name) const;
    Function* getFunctionByDemangledName(std::string name) const;
    std::string demangle(std::string name) const;

    std::unique_ptr<SymbolicState> createGlobalState(llvm::Module* module);

    void keepModule(std::unique_ptr<llvm::Module> module);

private:
    std::vector<std::unique_ptr<Function>> functions;
    llvm::Module* activeModule;

    std::vector<std::unique_ptr<llvm::Module>> storedModules;
};