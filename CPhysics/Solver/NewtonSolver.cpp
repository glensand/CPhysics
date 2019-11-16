#include "NewtonSolver.h"

namespace
{
inline CPhysics::Real dydx(const CPhysics::Function1d &function, CPhysics::Real x0, CPhysics::Real acc)
{
	return (function(x0 + acc) - function(x0 - acc)) / (2 * acc);
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

	const auto solverParams = reinterpret_cast<const OneDimensionalSolverParams*>(params);

	const Real a = solverParams->m_leftX;
	const Real b = solverParams->m_rightX;
	const auto function = solverParams->m_function;
	
	for (Real x0 = (a + b) / 2;x0 < b && x0 > a;)
	{
		const Real x1 = x0 - function(x0) / dydx(function, x0, solverParams->m_accuracy);
		if (std::abs(x1 - x0) <= solverParams->m_accuracy)
			return (x1 + x0) / 2;

		x0 = x1;
	}

	return Real(0);
}
//------------------------------------------------------------------------------
std::unique_ptr<ByStepResult> NewtonSolver::SolveByStep(const Params* params) const
{
	auto res = std::make_unique<NewtonByStepResult>();
	if (!SuitableParams(params)) return res;

	const auto solverParams = reinterpret_cast<const OneDimensionalSolverParams*>(params);

	const Real a = solverParams->m_leftX;
	const Real b = solverParams->m_rightX;
	const auto function = solverParams->m_function;

	for (Real x0 = (a + b) / 2; x0 < b && x0 > a;)
	{
		const auto dy = dydx(function, x0, solverParams->m_accuracy);
		const auto y = function(x0);
		const Real x1 = x0 - y / dy;

		res->m_dy.emplace_back(dy);
		res->m_xs.emplace_back(x0);
		res->m_ys.emplace_back(y);
		if (std::abs(x1 - x0) <= solverParams->m_accuracy)
		{
			res->m_res = (x1 + x0) / 2;
			return res;
		}

		x0 = x1;
	}

	return res;
}
//------------------------------------------------------------------------------
}
