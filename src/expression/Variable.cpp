#include "Variable.h"

#include "state/ISymbolicState.h"

static int counter = 0;

Variable::Variable(llvm::Value* value, uint64_t count)
    : Variable(value, count, nullptr)
{

}
Variable::Variable(llvm::Value* value, uint64_t count, Expression* content)
    : MemoryLocation(value, content, count)
{

}

std::string Variable::getIdentifier()
{
    if (this->identifier == "")
    {
        this->identifier = "unknown_var_" + std::to_string(counter++);
    }

    return this->identifier;
}
void Variable::setIdentifier(std::string identifier)
{
    this->identifier = identifier;
}

std::unique_ptr<Expression> Variable::clone()
{
    std::unique_ptr<Variable> var = std::make_unique<Variable>(this->getValue(), this->getCount());
    var->setContent(this->getContent());
    var->setIdentifier(this->getIdentifier());

    std::unique_ptr<Expression> ret = std::unique_ptr<Expression>(var.get());
    var.release();
    return ret;
}

std::unique_ptr<Expression> Variable::deepClone(ISymbolicState* state)
{
    if (this->isUndefined())
    {
        return std::make_unique<Variable>(this->getValue(), this->getCount());
    }

    std::unique_ptr<Expression> content = this->getContent()->deepClone(state);
    state->addExpr(content->getValue(), content.get());
    content.release();

    std::unique_ptr<Expression> var = std::make_unique<Variable>(this->getValue(),
                                      this->getCount(),
                                      state->getExpr(this->getContent()->getValue()));
    (static_cast<Variable*>(var.get()))->setIdentifier(this->getIdentifier());
    return var;
}
