#include "DichotomySolver.h"

namespace CPhysics
{
//------------------------------------------------------------------------------
std::string DichotomySolver::GetSolverType() const
{
	return "Dichotomy method";
}
//------------------------------------------------------------------------------
Real DichotomySolver::Solve(const Params* params) const
{
	if (!SuitableParams(params)) return Real();

	const auto dichotomySolverParams = reinterpret_cast<const OneDimensionalParams*>(params);

	Real a = dichotomySolverParams->m_leftX;
	Real b = dichotomySolverParams->m_rightX;
	const auto function = dichotomySolverParams->m_function;

	for(;b - a > dichotomySolverParams->m_accuracy;)
	{
		const auto ab2 = (a + b) / 2;
		const auto fab2 = function(ab2);

		if (std::abs(fab2) < dichotomySolverParams->m_accuracy)
			return ab2;
		
		if (function(a) * fab2 <= .0)
			b = ab2;
		else
			a = ab2;
	}
	
	return (a + b) / 2;
}
//------------------------------------------------------------------------------
}
