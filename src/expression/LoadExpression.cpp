#include "LoadExpression.h"

#include <llvm/IR/Value.h>
#include <llvm/IR/Type.h>

#include "path/Path.h"
#include "util/Logger.h"

LoadExpression::LoadExpression(llvm::Value* value, MemoryLocation* source)
        : MemoryLocation(value, source, 1)
{

}

void LoadExpression::dump(int priority)
{
    Logger::get().log(priority, "Load: ");
    this->getSource()->dump(priority);
}

z3::expr LoadExpression::createConstraint(Path* path)
{
    return this->getSource()->createConstraint(path);
}

bool LoadExpression::isLoad() const
{
    return true;
}
MemoryLocation* LoadExpression::getSource() const
{
    return static_cast<MemoryLocation*>(this->getContent());
}

std::string LoadExpression::getIdentifier()
{
    return this->getSource()->getIdentifier();
}

std::unique_ptr<Expression> LoadExpression::clone()
{
    return std::make_unique<LoadExpression>(this->getValue(), this->getSource());
}

std::unique_ptr<Expression> LoadExpression::deepClone(ISymbolicState* state)
{
    std::unique_ptr<Expression> source = this->getSource()->deepClone(state);
    state->addExpr(source->getValue(), source.get());
    source.release();

    assert(state->hasExpr(this->getSource()->getValue()));

    return std::make_unique<LoadExpression>(this->getValue(),
                                            static_cast<MemoryLocation*>(state->getExpr(this->getSource()->getValue())));
}
