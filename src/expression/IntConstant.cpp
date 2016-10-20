#include <util/Logger.h>
#include "IntConstant.h"

#include "path/Path.h"

IntConstant::IntConstant(llvm::Value* value, int64_t constant)
        : Expression(value), constant(constant)
{

}

void IntConstant::dump(int priority)
{
    Logger::get().line(priority, "Int(%)", this->constant);
}

z3::expr IntConstant::createConstraint(Path* path)
{
    return path->getContext().int_val(static_cast<int>(this->constant));
}
