#pragma once

#include <memory>
#include <vector>

#include "declaration.h"
#include "path.h"

namespace llvm {
    class Function;
}

class Function
{
public:
    Function(llvm::Function* handle);

    llvm::Function* getHandle() const;

    std::string getName() const;
    llvm::Type* getReturnType() const;
    const std::vector<Declaration>& getParameters() const;
    Path* getActivePath() const;

private:
    llvm::Function* handle;

    std::vector<Declaration> parameters;

    size_t activePath = 0;
    std::vector<std::unique_ptr<Path>> paths;
};