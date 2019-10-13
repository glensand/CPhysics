#include "RungeKutta2SystemSolver.h"

namespace CPhysics {

RungeKutta2SystemSolver::ReturnType RungeKutta2SystemSolver::Solve(const Params* params) const
{
	if (!SuitableParams(params)) return ReturnType{};
	const auto sds_params = reinterpret_cast<const ODSParams*>(params);

	std::vector<Real> x{};
	std::vector<std::vector<Real>> Y{sds_params->m_functions.size(), std::vector<Real>{}};
	
	const Real length = sds_params->m_right_x - sds_params->m_left_x;
	const Real step = length / sds_params->m_knot_amount;
	x.push_back(sds_params->m_left_x);
	
	for (size_t i = 0; i < sds_params->m_functions.size(); ++i)
	{
		Y[i].push_back(sds_params->m_conditions[i]);
	}
	
	for (size_t i = 1; i <= sds_params->m_knot_amount; ++i)
	{
		x.push_back(x[i - 1] + step);
		for (size_t j = 0; j < sds_params->m_functions.size(); ++j)
		{
			std::vector<Real> args{};
			args.push_back(x[i - 1]);
			for (auto it : Y)
			{
				args.push_back(it[i - 1]);
			}
			std::vector<Real> args_modified{};
			args_modified.push_back(x[i - 1] + 2 * step / 3);
			for (size_t k = 0; k < Y.size(); ++k)
			{
				args_modified.push_back(Y[k][i - 1] + 2 * step * sds_params->m_functions[k](args) / 3);
			}
			Real y = Y[j][i - 1] + step *
					(0.25 * sds_params->m_functions[j](args) +
					0.75 * sds_params->m_functions[j](args_modified));
			Y[j].push_back(y);
		}
	}	
	Y.insert(Y.begin(), x);
	return Y;
}

}