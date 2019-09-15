#include "DichotomySolver.h"

namespace CPhysics
{
std::string DichotomySolver::GetSolverType() const
{
	return "Dichotomy method";
}

Real DichotomySolver::Solve(OneDimensionalFunction function, Real leftX, Real rightX) const
{

	return Real();
}

}
