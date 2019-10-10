#include "RungeKutta2Solver.h"
#include "Euler2Solver.h"

namespace CPhysics
{

std::string RungeKutta2Solver::GetSolverType() const
{
	return "Runge-Kutta second precision degree ordinary differential equation solver";
}

bool RungeKutta2Solver::SuitableParams(const Params* params) const
{
	const auto Eparam = dynamic_cast<const SimpleDifferentialParams*>(params);
	if (Eparam)
		return Eparam->m_rightX >= Eparam->m_leftX;

	return false;
}

std::vector<std::pair<CPhysics::Real, CPhysics::Real>> RungeKutta2Solver::Solve(
	const Params* params) const
{
	if (!SuitableParams(params)) return std::vector<std::pair<Real, Real>>{};
	
	auto sdParams = reinterpret_cast<const SimpleDifferentialParams*>(params);
	Real length = sdParams->m_rightX - sdParams->m_leftX;
	Real step = length / sdParams->m_knotAmount;
	
	std::vector<std::pair<Real, Real>> res{};
	res.emplace_back(sdParams->m_leftX, sdParams->m_leftCond);

	for (size_t i = 1; i <= sdParams->m_knotAmount; ++i) 
	{
		Real x = res[i - 1].first + step;
		Real y =	res[i - 1].first + step *
					(0.25 * sdParams->m_function(res[i - 1].first, res[i - 1].second) +
					0.75 * sdParams->m_function(res[i - 1].first + 2 * step / 3, 
					res[i - 1].second +	
					2 * step * sdParams->m_function(res[i - 1].first, res[i - 1].second) / 3));
		res.emplace_back(x, y);
	}
	return res;
}
	
}










