#include "IndexExpression.h"

#include "path/Path.h"

IndexExpression::IndexExpression(llvm::Value* value, MemoryLocation* base, int64_t index)
    : MemoryLocation(value, nullptr, 1), index(index), base(base)
{

}
IndexExpression::IndexExpression(llvm::Value* value, MemoryLocation* base, std::vector<std::shared_ptr<Expression>> indices)
    : MemoryLocation(value, nullptr, 1), base(base), indices(std::move(indices))
{

}

z3::expr IndexExpression::createConstraint(Path* path)
{
    // TODO
    return z3::expr(path->getContext());
}

void IndexExpression::setContent(Expression* expression)
{
    // TODO
}

const std::string& IndexExpression::getIdentifier() const
{
    return this->base->getIdentifier() + "[" + std::to_string(this->index) + "]";
}
