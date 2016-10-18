#include <pass.h>

static llvm::RegisterPass<SEPass> SE("se", "SE Pass", false, true);
