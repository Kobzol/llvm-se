#include "UnknownExpression.h"

#include "path/Path.h"
#include "util/Logger.h"

static int unknownCount = 0;

UnknownExpression::UnknownExpression(llvm::Value *value): Expression(value)
{

}

void UnknownExpression::dump(int priority, int indent)
{
    Logger::get().line(priority, indent, "Unknown");
}

z3::expr UnknownExpression::createConstraint(Path* path)
{
    return path->getContext().int_const(("unknown_" + std::to_string(unknownCount)).c_str());
}

bool UnknownExpression::isUnknown() const
{
    return true;
}

std::unique_ptr<Expression> UnknownExpression::deepClone(ISymbolicState* state)
{
    return std::make_unique<UnknownExpression>(this->getValue());
}
