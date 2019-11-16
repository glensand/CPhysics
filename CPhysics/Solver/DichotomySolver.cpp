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

	const auto dichotomySolverParams = reinterpret_cast<const OneDimensionalSolverParams*>(params);

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
std::unique_ptr<ByStepResult> DichotomySolver::SolveByStep(const Params* params) const
{
	auto res = std::make_unique<ByStepD1Result>();
	if (!SuitableParams(params)) return res;

	const auto dichotomySolverParams = reinterpret_cast<const OneDimensionalSolverParams*>(params);

	Real a = dichotomySolverParams->m_leftX;
	Real b = dichotomySolverParams->m_rightX;
	const auto function = dichotomySolverParams->m_function;

	for (; b - a > dichotomySolverParams->m_accuracy;)
	{
		const auto ab2 = (a + b) / 2;
		const auto fab2 = function(ab2);

		res->m_xs.emplace_back(ab2);
		res->m_ys.emplace_back(fab2);

		if (std::abs(fab2) < dichotomySolverParams->m_accuracy)
		{
			res->m_res = ab2;
			return  res;
		}

		if (function(a) * fab2 <= .0)
			b = ab2;
		else
			a = ab2;
	}

	res->m_res = (a + b) / 2;
	return res;
}
//------------------------------------------------------------------------------
}
