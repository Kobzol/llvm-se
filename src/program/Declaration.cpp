#include "Declaration.h"

Declaration::Declaration(std::string name, llvm::Type* type): name(std::move(name)), type(type)
{

}

std::string Declaration::getName() const
{
    return this->name;
}

llvm::Type* Declaration::getType() const
{
    return this->type;
}
