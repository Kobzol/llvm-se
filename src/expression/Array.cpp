#include "Array.h"

#include "path.h"

Array::Array(llvm::Value* value, std::string name, uint64_t size): MemoryLocation(value, nullptr, name), size(size)
{

}

z3::expr Array::createConstraint(Path* path)
{
    return z3::expr(path->getContext());
}
