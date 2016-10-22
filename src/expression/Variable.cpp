#include "Variable.h"

Variable::Variable(llvm::Value* value, uint64_t count)
    : Variable(value, count, nullptr)
{

}
Variable::Variable(llvm::Value* value, uint64_t count, Expression* content)
    : MemoryLocation(value, content, count)
{

}

std::string Variable::getIdentifier() const
{
    return this->identifier;
}
void Variable::setIdentifier(std::string identifier)
{
    this->identifier = identifier;
}
