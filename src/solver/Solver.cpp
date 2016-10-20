#include "Solver.h"

Solver::Solver(z3::context* ctx): ctx(ctx), solver(*ctx)
{

}
Solver::Solver(const Solver& other)
        : ctx(other.ctx), solver(this->copySolver(other.solver))
{

}

Solver& Solver::operator=(const Solver& other)
{
    this->solver = this->copySolver(other.solver);
    return *this;
}

z3::solver Solver::copySolver(const z3::solver& solver)
{
    return z3::solver(this->getContext(), Z3_solver_translate(this->getContext(), solver, this->getContext()));
}

void Solver::addConstraint(const z3::expr& e)
{
    this->solver.add(e);
}

bool Solver::isSatisfiable()
{
    return this->isSatisfiable(this->getContext().bool_val(true));
}
bool Solver::isSatisfiable(const z3::expr& e)
{
    z3::solver s = this->copySolver(this->solver);
    s.add(e);
    return s.check() == z3::check_result::sat;
}

z3::context& Solver::getContext()
{
    return *this->ctx;
}
