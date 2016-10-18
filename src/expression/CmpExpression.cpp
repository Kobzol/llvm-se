#include "CmpExpression.h"

#include "path.h"
#include "util/logger.h"

CmpExpression::CmpExpression(llvm::Value* value, Expression* lhs, Expression* rhs, llvm::CmpInst::Predicate predicate)
    : BinaryExpression(value, lhs, rhs), predicate(predicate)
{

}

void CmpExpression::dump(int priority)
{
    Logger::get().line(priority, "Cmp");
    BinaryExpression::dump(priority);
}

z3::expr CmpExpression::createConstraint(Path* path)
{
    z3::expr lhs = this->getLHS()->createConstraint(path);
    z3::expr rhs = this->getRHS()->createConstraint(path);

    switch (this->predicate)
    {
        case llvm::CmpInst::Predicate::ICMP_EQ: return lhs == rhs;
        case llvm::CmpInst::Predicate::ICMP_NE: return lhs != rhs;
        case llvm::CmpInst::Predicate::ICMP_SLT: return lhs < rhs;
        case llvm::CmpInst::Predicate::ICMP_SLE: return lhs <= rhs;
        case llvm::CmpInst::Predicate::ICMP_SGT: return lhs > rhs;
        case llvm::CmpInst::Predicate::ICMP_SGE: return lhs >= rhs;
    }

    Logger::get().line(Logger::Prio::WARNING, "Unknown cmp predicate %", this->predicate);

    return z3::expr(path->getContext());
}