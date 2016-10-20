#include "MemoryLocation.h"

#include <llvm/IR/Type.h>

#include "path/Path.h"
#include "util/Logger.h"

MemoryLocation::MemoryLocation(llvm::Value* value, Expression* content, uint64_t count)
        : Expression(value), content(content), identifier(identifier), count(count)
{

}

void MemoryLocation::dump(int priority)
{
    Logger::get().line(priority, this->getIdentifier());
}

Expression* MemoryLocation::getContent() const
{
    return this->content;
}
void MemoryLocation::setContent(Expression* content)
{
    this->content = content;
}

bool MemoryLocation::isUndefined() const
{
    return this->content == nullptr;
}

bool MemoryLocation::hasIdentifier() const
{
    return this->getIdentifier() != "";
}
const std::string& MemoryLocation::getIdentifier() const
{
    return this->identifier;
}
void MemoryLocation::setIdentifier(std::string identifier)
{
    this->identifier = identifier;
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
