#include "IntConstant.h"

#include "path/Path.h"
#include "solver/ExprTracker.h"
#include "util/Logger.h"

IntConstant::IntConstant(llvm::Value* value, int64_t constant)
        : Expression(value), constant(constant)
{

}

void IntConstant::dump(int priority, int indent)
{
    Logger::get().line(priority, indent, "Int % (%)", this->constant, this->getValue());
}

z3::expr IntConstant::createConstraint(Path* path)
{
    return path->getContext().int_val(static_cast<int>(this->constant));
}

bool IntConstant::isConstant() const
{
    return true;
}

int64_t IntConstant::getConstant() const
{
    return this->constant;
}

std::unique_ptr<Expression> IntConstant::deepClone(ISymbolicState* state)
{
    return std::make_unique<IntConstant>(this->getValue(), this->constant);
}
