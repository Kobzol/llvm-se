#include "MemoryCompileAction.h"


MemoryCompileAction::MemoryCompileAction(std::unique_ptr<llvm::Module>* holder, llvm::LLVMContext& context): EmitLLVMOnlyAction(&context), holder(holder)
{

}

MemoryCompileAction::~MemoryCompileAction()
{
    *this->holder = this->takeModule();
    assert(this->holder->get());
}
