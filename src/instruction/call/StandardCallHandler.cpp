#include "StandardCallHandler.h"

#include <llvm/IR/Instructions.h>
#include <expression/ExprBuilder.h>

#include "path/PathGroup.h"

bool StandardCallHandler::shouldHandle(const CallInfo& info) const
{
    return true;
}

void StandardCallHandler::handle(const CallInfo& info) const
{
    llvm::Function* fn = info.getInst()->getCalledFunction();
    assert(fn); // indirect call

    Path* path = info.getPath();
    PathGroup pg(path->getGroup()->getContext());

    {
        std::unique_ptr<Path> callPath = std::make_unique<Path>(path->getState()->getStates(),
                                                                &pg,
                                                                Function(fn).getFirstInstruction());

        this->addParameters(info.getInst(), path, callPath.get());

        pg.addPath(std::move(callPath));
        pg.exhaust();
    }

    assert(pg.getPaths().size() == 1);
    Path* p = pg.getPaths()[0].get();
    p->mergeGlobalsTo(path);

    std::unique_ptr<Expression> retVal = p->getReturnValue()->deepClone(path->getState()->getLocalState());
    path->getState()->addExpr(info.getInst(), retVal.get());
    retVal.release();

    CallHandler::handle(info);
}

void StandardCallHandler::addParameters(llvm::CallInst* call, Path* callingPath, Path* calledPath) const
{
    llvm::Function* fn = call->getCalledFunction();
    ExprBuilder builder(callingPath->getState());

    unsigned int i = 0;
    for (llvm::Argument& arg : fn->getArgumentList())
    {
        llvm::Value* param = call->getArgOperand(i);

        Expression* expr = builder.build(param);
        std::unique_ptr<Expression> cloned = expr->deepClone(calledPath->getState());
        calledPath->getState()->addExpr(&arg, cloned.get());
        cloned.release();
        i++;
    }
}
