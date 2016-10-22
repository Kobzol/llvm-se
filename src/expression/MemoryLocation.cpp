#include "MemoryLocation.h"

#include <llvm/IR/Type.h>

#include "path/Path.h"
#include "util/Logger.h"

MemoryLocation::MemoryLocation(llvm::Value* value, Expression* content, uint64_t count)
        : Expression(value), content(content), count(count)
{

}

void MemoryLocation::dump(int priority)
{
    Logger::get().line(priority, "% (%)", this->getIdentifier(), this->getValue());
}

Expression* MemoryLocation::getContent() const
{
    return this->content;
}
void MemoryLocation::setContent(Expression* content)
{
    this->content = content;
}

uint64_t MemoryLocation::getCount() const
{
    return this->count;
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
        this->dump(1);
        throw "1";
    }

    return this->getContent()->createConstraint(path);
}

bool MemoryLocation::isMemoryLocation() const
{
    return true;
}

MemoryLocation* MemoryLocation::getOrigin()
{
    MemoryLocation* loc = this;

    while (loc->getContent() != nullptr && loc->getContent()->isMemoryLocation())
    {
        loc = static_cast<MemoryLocation*>(loc->getContent());
    }

    return loc;
}
