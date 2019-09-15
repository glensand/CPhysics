#include "NewtonSolver.h"

namespace CPhysics
{
std::string NewtonSolver::GetSolverType() const
{
	return "Newton method";
}

Real NewtonSolver::Solve(OneDimensionalFunction function, Real leftX, Real rightX) const
{

	return Real();
}

}
