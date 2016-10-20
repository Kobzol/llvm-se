#pragma once

#include <memory>
#include <vector>

#include "path/SymbolicState.h"
#include "program/Function.h"

namespace llvm {
    class Module;
}

class Context
{
public:
    llvm::Module* getActiveModule() const;
    void handleModule(llvm::Module* module);

    Function* getFunctionByName(std::string name) const;

    std::unique_ptr<SymbolicState> createGlobalState(llvm::Module* module);

private:
    std::vector<std::unique_ptr<Function>> functions;
    llvm::Module* activeModule;
};