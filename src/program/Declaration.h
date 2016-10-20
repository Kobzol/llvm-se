#pragma once

#include <string>

namespace llvm {
    class Type;
}

class Declaration
{
public:
    Declaration(std::string name, llvm::Type* type);

    std::string getName() const;
    llvm::Type* getType() const;

private:
    std::string name;
    llvm::Type* type;
};