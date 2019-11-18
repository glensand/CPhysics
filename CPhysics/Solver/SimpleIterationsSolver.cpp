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
		const auto res = function(x) + x;
		if (std::abs(res - x) < solverParams->m_accuracy) return x;

		x = res;
	}
}
//------------------------------------------------------------------------------
std::unique_ptr<ByStepResult> SimpleIterationsSolver::SolveByStep(const Params* params) const
{
	auto result = std::make_unique<ByStepD1Result>();
	if (!SuitableParams(params)) return result;

	const auto solverParams = reinterpret_cast<const OneDimensionalSolverParams*>(params);

	const auto function = solverParams->m_function;
	const auto x0{ (solverParams->m_leftX + solverParams->m_rightX) / 2 };

	const auto lambda{ (function(x0 + solverParams->m_accuracy) - function(x0 - solverParams->m_accuracy)) / (2 * solverParams->m_accuracy) };

	for (Real x{ x0 };;)
	{
		const auto y = function(x);
		const auto res = x -  y / lambda;

		result->m_xs.emplace_back(x);
		result->m_ys.emplace_back(y);
		
		if (std::abs(res - x) < solverParams->m_accuracy)
		{
			result->m_res = res;
			return result;
		}

		x = res;
	}
}
//------------------------------------------------------------------------------
}
