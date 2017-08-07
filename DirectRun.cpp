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
    z3::context ctx;
    z3::expr i1 = ctx.int_const("x");
    z3::expr cond = i1 < ctx.int_val(5);

    z3::solver s(ctx);
    s.add(!cond);
    s.check();
    z3::model m = s.get_model();
    for (unsigned i = 0; i < m.size(); i++) {
        z3::func_decl v = m[i];
        // this problem contains only constants
        assert(v.arity() == 0);
        std::cout << v.name() << " = " << m.get_const_interp(v) << "\n";
    }
    // we can evaluate expressions in the model.
    std::cout << "x = " << m.eval(i1) << "\n";



    /*std::string code = readFile(argv[1]);

    std::unique_ptr<llvm::Module> module = MemoryCompiler::get().compile(code);
    Context ctx;
    ctx.handleModule(module.get());

    for (auto& error : ctx.getErrors())
    {
        error->dump(Logger::Prio::ERROR);
    }*/

    return 0;
}
