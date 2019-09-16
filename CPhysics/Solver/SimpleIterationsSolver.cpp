#include "SimpleIterationsSolver.h"

namespace CPhysics
{
std::string SimpleIterationsSolver::GetSolverType() const
{
	return "Simple iterations method";
}

Real SimpleIterationsSolver::Solve(const Params* params) const
{
	if (!SuitableParams(params)) return Real();

	const auto simpleIterationsSolverParams = reinterpret_cast<const OneDimensionalParams*>(params);

	const auto function = simpleIterationsSolverParams->m_function;
	Real x = (simpleIterationsSolverParams->m_leftX + simpleIterationsSolverParams->m_rightX) / 2;
	
	for (; std::abs(function(x) - x) > simpleIterationsSolverParams->m_accuracy;)
		x = function(x);

	return x;
}

}
