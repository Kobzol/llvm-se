#include "BinaryExpression.h"

#include "util/logger.h"

BinaryExpression::BinaryExpression(llvm::Value* value, Expression* lhs, Expression* rhs)
    : Expression(value), lhs(lhs), rhs(rhs)
{

}

Expression* BinaryExpression::getLHS() const
{
    return this->lhs;
}
Expression* BinaryExpression::getRHS() const
{
    return this->rhs;
}

void BinaryExpression::dump(int priority)
{
    Logger::get().log(priority, "LHS: ");
    this->lhs->dump(priority);
    Logger::get().log(priority, "RHS: ");
    this->rhs->dump(priority);
}
