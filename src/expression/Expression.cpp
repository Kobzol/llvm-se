#include "Expression.h"

#include <llvm/IR/Value.h>

#include "util/Logger.h"

Expression::Expression(llvm::Value* value): value(value)
{

}

llvm::Value* Expression::getValue() const
{
    return this->value;
}
llvm::Type* Expression::getType() const
{
    return this->value->getType();
}

void Expression::dump(int priority)
{
    if (Logger::get().checkPriority(priority))
    {
        this->value->dump();
    }
}

bool Expression::isConstant() const
{
    return false;
}
bool Expression::isMemoryLocation() const
{
    return false;
}
