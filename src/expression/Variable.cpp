#include "Variable.h"

Variable::Variable(llvm::Value* value, uint64_t count)
    : Variable(value, count, nullptr)
{

}
Variable::Variable(llvm::Value* value, uint64_t count, Expression* content)
    : MemoryLocation(value, content, count)
{

}

z3::expr Variable::createConstraint(Path* path)
{
    if (this->isUndefined())
    {
        throw "1";
    }

    return this->getContent()->createConstraint(path);
}
