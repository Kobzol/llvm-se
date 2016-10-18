#include "Scalar.h"

#include "path.h"

Scalar::Scalar(llvm::Value* value, std::string name)
    : MemoryLocation(value, nullptr, name)
{

}
Scalar::Scalar(llvm::Value* value, Expression* content, std::string name)
        : MemoryLocation(value, content, name)
{

}

z3::expr Scalar::createConstraint(Path* path)
{
    return this->createConstExpr(path);
}
