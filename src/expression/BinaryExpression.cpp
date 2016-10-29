#include "BinaryExpression.h"

#include "solver/ExprTracker.h"
#include "state/ISymbolicState.h"
#include "util/Logger.h"

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

void BinaryExpression::dump(int priority, int indent)
{
    Logger::get().line(priority, indent, "LHS");
    this->lhs->dump(priority, indent + 1);
    Logger::get().line(priority, indent, "RHS");
    this->rhs->dump(priority, indent + 1);
}

bool BinaryExpression::isConstant() const
{
    return this->lhs->isConstant() && this->rhs->isConstant();
}

std::unique_ptr<Expression> BinaryExpression::deepClone(ISymbolicState* state)
{
    std::unique_ptr<Expression> exprs[2] = {
            this->getLHS()->deepClone(state),
            this->getRHS()->deepClone(state)
    };
    for (int i = 0; i < 2; i++)
    {
        state->addExpr(exprs[i]->getValue(), exprs[i].get());
        exprs[i].release();
    }

    return std::unique_ptr<BinaryExpression>();
}

void BinaryExpression::markAddresses(ExprTracker* tracker) const
{
    tracker->addAddress(this->getValue());
    this->getLHS()->markAddresses(tracker);
    this->getRHS()->markAddresses(tracker);
}
