#include "NewtonSolver.h"

namespace
{
inline CPhysics::Real dydx(CPhysics::OneDimensionalFunction function, CPhysics::Real x0, CPhysics::Real x1)
{
	return (function(x1) - function(x0)) / (x1 - x0);
}

}

namespace CPhysics
{
//------------------------------------------------------------------------------	
std::string NewtonSolver::GetSolverType() const
{
	return "Newton method";
}
//------------------------------------------------------------------------------
Real NewtonSolver::Solve(const Params* params) const
{
	if (!SuitableParams(params)) return Real();

	const auto dichotomySolverParams = reinterpret_cast<const OneDimensionalParams*>(params);

	Real a = dichotomySolverParams->m_leftX;
	Real b = dichotomySolverParams->m_rightX;
	const auto function = dichotomySolverParams->m_function;

	Real x0 = (dichotomySolverParams->m_leftX + dichotomySolverParams->m_rightX) / 2;
	
	for (;;)
	{
		Real x1 = x0 - function(x0) / dydx(function, x0, x0 + dichotomySolverParams->m_accuracy);
		if (std::abs(x1 - x0) <= dichotomySolverParams->m_accuracy)
			return (x1 - x0) / 2;

		x0 = x1;
	}
}
//------------------------------------------------------------------------------
}
