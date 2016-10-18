#include "AddExpression.h"

#include "util/logger.h"

AddExpression::AddExpression(llvm::Value* value, Expression* lhs, Expression* rhs)
        : BinaryExpression(value, lhs, rhs)
{

}

void AddExpression::dump(int priority)
{
    Logger::get().line(priority, "Add");
    BinaryExpression::dump(priority);
}

z3::expr AddExpression::createConstraint(Path* path)
{
    return this->getLHS()->createConstraint(path) + this->getRHS()->createConstraint(path);
}
