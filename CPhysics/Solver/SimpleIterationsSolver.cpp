#include "SimpleIterationsSolver.h"

namespace CPhysics
{
std::string SimpleIterationsSolver::GetSolverType() const
{
	return "Simple iterations method";
}

Real SimpleIterationsSolver::Solve(OneDimensionalFunction function, Real leftX, Real rightX) const
{

	return Real();
}

}
