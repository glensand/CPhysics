#include "RungeKutta2SystemSolver.h"

namespace CPhysics
{
//------------------------------------------------------------------------------	
std::string RungeKutta2SystemSolver::GetSolverType() const
{
	return "Numerical solver of systems of ordinary differential equations, Runge-Kutta 2nd order method.";
}
//------------------------------------------------------------------------------
RungeKutta2SystemSolver::ReturnType RungeKutta2SystemSolver::Solve(const Params* params) const
{
	if (!SuitableParams(params)) return ReturnType{};
	const auto sdsParams = reinterpret_cast<const ODSParams*>(params);

	std::vector<Real> x{};
	std::vector<std::vector<Real>> Y{sdsParams->m_functions.size(), std::vector<Real>{}};
	
	const Real length = sdsParams->m_right_x - sdsParams->m_left_x;
	const Real step = length / sdsParams->m_knotAmount;
	x.push_back(sdsParams->m_left_x);
	
	for (size_t i = 0; i < sdsParams->m_functions.size(); ++i)
		Y[i].push_back(sdsParams->m_conditions[i]);
	
	for (size_t i = 1; i <= sdsParams->m_knotAmount; ++i)
	{
		x.push_back(x[i - 1] + step);
		for (size_t j = 0; j < sdsParams->m_functions.size(); ++j)
		{
			std::vector<Real> xes{};
			const Real xN = x[i - 1];
			for (const auto &it : Y)
				xes.push_back(it[i - 1]);

			std::vector<Real> argsModified{};
			const Real x_n_modified = x[i - 1] + 2 * step / 3;
			for (size_t k = 0; k < Y.size(); ++k)
				argsModified.push_back(Y[k][i - 1] + 2 * step * sdsParams->m_functions[k](xN, xes) / 3);
			
			const Real y = Y[j][i - 1] + step *
					(0.25 * sdsParams->m_functions[j](xN, xes) +
					0.75 * sdsParams->m_functions[j](x_n_modified, argsModified));
			Y[j].push_back(y);
		}
	}	
	Y.insert(Y.begin(), x);
	return Y;
}
//------------------------------------------------------------------------------
}