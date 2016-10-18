#include "UnknownExpression.h"

#include "path.h"
#include "util/logger.h"

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
