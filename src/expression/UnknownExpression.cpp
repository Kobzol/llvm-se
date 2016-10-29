#include "UnknownExpression.h"

#include "path/Path.h"
#include "util/Logger.h"

UnknownExpression::UnknownExpression(llvm::Value *value): Expression(value)
{

}

void UnknownExpression::dump(int priority)
{
    Logger::get().line(priority, "Unknown");
}

z3::expr UnknownExpression::createConstraint(Path* path)
{
    return path->getContext().bool_val(true);
}

bool UnknownExpression::isUnknown() const
{
    return true;
}

std::unique_ptr<Expression> UnknownExpression::deepClone(ISymbolicState* state)
{
    return std::make_unique<UnknownExpression>(this->getValue());
}
