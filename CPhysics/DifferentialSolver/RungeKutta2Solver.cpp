#include "RungeKutta2Solver.h"
#include "Euler2Solver.h"

namespace CPhysics
{
//------------------------------------------------------------------------------
std::string RungeKutta2Solver::GetSolverType() const
{
	return "Runge-Kutta m_y precision degree ordinary differential equation solver";
}
//------------------------------------------------------------------------------
bool RungeKutta2Solver::SuitableParams(const Params* params) const
{
	const auto eParam = dynamic_cast<const SimpleDifferentialParams*>(params);
	if (eParam)
		return eParam->m_rightX >= eParam->m_leftX;

	return false;
}
//------------------------------------------------------------------------------
std::vector<Point2D> RungeKutta2Solver::Solve(
	const Params* params) const
{
	if (!SuitableParams(params)) return std::vector<Point2D>();
	
	const auto sdParams = reinterpret_cast<const SimpleDifferentialParams*>(params);
	const Real length = sdParams->m_rightX - sdParams->m_leftX;
	const Real step = length / sdParams->m_knotAmount;
	
	std::vector<Point2D> res;
	res.emplace_back(sdParams->m_leftX, sdParams->m_leftCond);

	for (size_t i = 1; i <= sdParams->m_knotAmount; ++i) 
	{
		Real x = res[i - 1].m_x + step;
		Real y =	res[i - 1].m_y + step *
					(0.25 * sdParams->m_function(res[i - 1].m_x, res[i - 1].m_y) +
					0.75 * sdParams->m_function(res[i - 1].m_x + 2 * step / 3, 
					res[i - 1].m_y +	
					2 * step * sdParams->m_function(res[i - 1].m_x, res[i - 1].m_y) / 3));
		res.emplace_back(x, y);
	}
	return res;
}
//------------------------------------------------------------------------------
}










