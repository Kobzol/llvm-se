#include "AddExpression.h"

#include "state/ISymbolicState.h"
#include "util/Logger.h"

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

std::unique_ptr<Expression> AddExpression::deepClone(ISymbolicState* state)
{
    BinaryExpression::deepClone(state);

    return std::make_unique<AddExpression>(this->getValue(),
                                           state->getExpr(this->getLHS()->getValue()),
                                           state->getExpr(this->getRHS()->getValue())
    );
}
