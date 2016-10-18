#include "LoadExpression.h"

#include "path.h"
#include "util/logger.h"

LoadExpression::LoadExpression(llvm::Value* value, Expression* source): Expression(value), source(source)
{

}

Expression* LoadExpression::getSource() const
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
