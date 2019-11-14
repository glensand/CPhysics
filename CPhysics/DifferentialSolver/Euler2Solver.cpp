#include "Euler2Solver.h"

namespace CPhysics {
//------------------------------------------------------------------------------
std::string Euler2Solver::GetSolverType() const
{
	return "Euler method 2nd order simple differential equation solver";
}
//------------------------------------------------------------------------------
std::vector<Point2D> Euler2Solver::Solve(const Params* params) const
{
	if (!SuitableParams(params)) return std::vector<Point2D>{};
	
	const auto eParams = reinterpret_cast<const Euler2Params*>(params);
	const Real length = eParams->m_rightX - eParams->m_leftX;
	const Real step = length / eParams->m_knotAmount;

	std::vector<Point2D> res;
	res.reserve(eParams->m_knotAmount);
	res.emplace_back(eParams->m_leftX, eParams->m_leftCond);
	
	for (size_t i = 1; i <= eParams->m_knotAmount; ++i)
	{
		Real x = res[i - 1].m_x + step;
		Real y =	res[i - 1].m_y +
					step * eParams->m_function(res[i - 1].m_x, res[i - 1].m_y) +
					step * step / 2 *	(eParams->m_functionByX(res[i - 1].m_x, res[i - 1].m_y) +
										eParams->m_functionByU(res[i - 1].m_x, res[i - 1].m_y) *
										eParams->m_function(res[i - 1].m_x, res[i - 1].m_y));
		res.emplace_back(x, y);
	}
	return res;
}
//------------------------------------------------------------------------------
bool Euler2Solver::SuitableParams(const Params* params) const
{
	const auto eParam = dynamic_cast<const Euler2Params*>(params);
	if (eParam)
		return eParam->m_rightX >= eParam->m_leftX;

	return false;
}
//------------------------------------------------------------------------------
}