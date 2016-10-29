#include <fstream>

#include "util/compile/MemoryCompiler.h"
#include "util/Logger.h"


std::string readFile(const char* path)
{
    std::fstream fs(path);
    assert(fs.is_open());

    std::stringstream buffer;
    buffer << fs.rdbuf();

    return buffer.str();
}

int main(int argc, char** argv)
{
    std::string code = readFile(argv[1]);

    std::unique_ptr<llvm::Module> module = MemoryCompiler::get().compile(code);
    Context ctx;
    ctx.handleModule(module.get());

    for (auto& error : ctx.getErrors())
    {
        error->dump(Logger::Prio::ERROR);
    }

    return 0;
}
