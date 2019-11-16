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

	const auto solverParams = reinterpret_cast<const OneDimensionalSolverParams*>(params);

	const auto function = solverParams->m_function;
	
	for (Real x = (solverParams->m_leftX + solverParams->m_rightX) / 2;;)
	{
		const auto res = function(x);
		if (std::abs(res - x) < solverParams->m_accuracy) return x;

		x = res;
	}
}
//------------------------------------------------------------------------------
std::unique_ptr<ByStepResult> SimpleIterationsSolver::SolveByStep(const Params* params) const
{
	// TODO: resolve 
	return  std::make_unique<ByStepD1Result>();
}
//------------------------------------------------------------------------------
}
