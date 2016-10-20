#include "IndexExpression.h"

#include "path/Path.h"

IndexExpression::IndexExpression(llvm::Value* value, const llvm::Value* pointer, int64_t index)
    : Expression(value), index(index), pointer(pointer)
{

}
IndexExpression::IndexExpression(llvm::Value* value, const llvm::Value* pointer, std::vector<std::shared_ptr<Expression>> indices)
    : Expression(value), pointer(pointer), indices(std::move(indices))
{

}

z3::expr IndexExpression::createConstraint(Path* path)
{
    return z3::expr(path->getContext());
}
