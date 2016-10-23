#include "Variable.h"

static int counter = 0;

Variable::Variable(llvm::Value* value, uint64_t count)
    : Variable(value, count, nullptr)
{

}
Variable::Variable(llvm::Value* value, uint64_t count, Expression* content)
    : MemoryLocation(value, content, count)
{

}

std::string Variable::getIdentifier()
{
    if (this->identifier == "")
    {
        this->identifier = "unknown_var_" + std::to_string(counter++);
    }

    return this->identifier;
}
void Variable::setIdentifier(std::string identifier)
{
    this->identifier = identifier;
}
