#include "MemoryLocation.h"

#include <llvm/IR/Value.h>
#include <llvm/IR/Type.h>

#include "path/Path.h"
#include "solver/ExprTracker.h"
#include "util/Logger.h"

MemoryLocation::MemoryLocation(llvm::Value* value, Expression* content, size_t count)
        : Expression(value), content(content), count(count),
          size(value->getType()->getContainedType(0)->getPrimitiveSizeInBits())
{

}

void MemoryLocation::dump(int priority, int indent)
{
    Logger::get().line(priority, indent, "Memloc % of size % (%)",
                       this->getIdentifier(),
                       this->getTotalSize(),
                       this->getValue()
    );
    if (!this->isUndefined())
    {
        this->getContent()->dump(priority, indent + 1);
    }
}

Expression* MemoryLocation::getContent() const
{
    return this->content;
}
void MemoryLocation::setContent(Expression* content)
{
    this->content = content;
}

size_t MemoryLocation::getCount() const
{
    return this->count;
}
size_t MemoryLocation::getTotalSize() const
{
    return this->getCount() * this->size;
}

bool MemoryLocation::isUndefined() const
{
    return this->content == nullptr;
}

z3::expr MemoryLocation::createConstExpr(Path* path)
{
    llvm::Type* type = this->getType();
    std::string name = this->getIdentifier();
    z3::context& ctx = path->getContext();

    if (type->isIntegerTy())
    {
        return ctx.int_const(name.c_str());
    }

    return ctx.int_const(name.c_str());
}

z3::expr MemoryLocation::createConstraint(Path* path)
{
    if (this->isUndefined())
    {
        this->dump(1, 0);
        throw "1";
    }

    return path->getContext().int_const(this->getIdentifier().c_str());
}

bool MemoryLocation::isMemoryLocation() const
{
    return true;
}

void MemoryLocation::markAddresses(ExprTracker* tracker) const
{
    tracker->addAddress(this->getValue());
    if (!this->isUndefined())
    {
        this->getContent()->markAddresses(tracker);
    }
}
