#include "SimpleIterationsSolver.h"

namespace CPhysics
{
//------------------------------------------------------------------------------
std::string SimpleIterationsSolver::GetSolverType() const
{
	return "Simple iterations method";
}
//------------------------------------------------------------------------------
Real SimpleIterationsSolver::Solve(const Params* params) const
{
	if (!SuitableParams(params)) return Real();

	const auto solverParams = reinterpret_cast<const OneDimensionalParams*>(params);

	const auto function = solverParams->m_function;
	Real x = (solverParams->m_leftX + solverParams->m_rightX) / 2;
	
	for (; std::abs(function(x) - x) > solverParams->m_accuracy;)
		x = function(x);

	return x;
}
//------------------------------------------------------------------------------
}
