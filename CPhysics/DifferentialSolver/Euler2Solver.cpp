#include "Euler2Solver.h"


namespace CPhysics {


std::string Euler2Solver::GetSolverType() const
{
	return "Euler method 2nd order simple differential equation solver";
}

	
std::vector<std::pair<Real, Real>> Euler2Solver::Solve(const Params* params) const
{
	if (!SuitableParams(params)) return std::vector<std::pair<Real, Real>>{};
	const auto eParams = reinterpret_cast<const Euler2Params*>(params);
	const Real length = eParams->m_rightX - eParams->m_leftX;
	const Real step = length / eParams->m_knotAmount;

	std::vector<std::pair<Real, Real>> res{};
	res.emplace_back(eParams->m_leftX, eParams->m_leftCond);
	
	for (size_t i = 1; i <= eParams->m_knotAmount; ++i)
	{
		Real x = res[i - 1].first + step;
		Real y =	res[i - 1].second +
					step * eParams->m_function(res[i - 1].first, res[i - 1].second) +
					step * step / 2 *	(eParams->m_functionByX(res[i - 1].first, res[i - 1].second) +
										eParams->m_functionByU(res[i - 1].first, res[i - 1].second) *
										eParams->m_function(res[i - 1].first, res[i - 1].second));
		res.emplace_back(x, y);
	}
	return res;
}
	
	
bool Euler2Solver::SuitableParams(const Params* params) const
{
	const auto Eparam = dynamic_cast<const Euler2Params*>(params);
	if (Eparam)
		return Eparam->m_rightX >= Eparam->m_leftX;

	return false;

}

}