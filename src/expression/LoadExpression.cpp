#include "LoadExpression.h"

#include "MemoryLocation.h"
#include "path/Path.h"
#include "util/Logger.h"

LoadExpression::LoadExpression(llvm::Value* value, MemoryLocation* source): Expression(value), source(source)
{

}

MemoryLocation* LoadExpression::getSource() const
{
    return this->source;
}

void LoadExpression::dump(int priority)
{
    Logger::get().log(priority, "Load: ");
    this->source->dump(priority);
}

z3::expr LoadExpression::createConstraint(Path* path)
{
    return this->getSource()->createConstraint(path);
}
