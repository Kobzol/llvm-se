#pragma once

#include <memory>
#include <vector>

#include "Declaration.h"

namespace llvm {
    class Function;
    class Instruction;
}

class Function
{
public:
    Function(llvm::Function* handle);

    llvm::Function* getHandle() const;

    bool isUser() const;

    std::string getName() const;
    llvm::Type* getReturnType() const;
    const std::vector<Declaration>& getParameters() const;

    llvm::Instruction* getFirstInstruction();

private:
    llvm::Function* handle;

    std::vector<Declaration> parameters;
};