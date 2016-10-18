#pragma once

#include <memory>
#include <vector>

#include "analysis/Analyser.h"
#include "program/function.h"

namespace llvm {
    class Module;
}

class Context
{
public:
    Context();

    llvm::Module* getActiveModule() const;
    void handleModule(llvm::Module* module);

    Function* getFunctionByName(std::string name) const;

private:
    std::vector<std::unique_ptr<Function>> functions;
    llvm::Module* activeModule;
    std::unique_ptr<Analyser> analyser;
};