#include "RungeKuttaSystemSolver.h"

#include <algorithm>

namespace CPhysics
{
	//------------------------------------------------------------------------------	
	std::string RungeKuttaSystemSolver::GetSolverType() const
	{
		return "Numerical solver of systems of ordinary differential equations, Runge-Kutta 4th order method.";
	}
	//------------------------------------------------------------------------------
	RungeKuttaSystemSolver::ReturnType RungeKuttaSystemSolver::Solve(const Params* params) const
	{
		if (!SuitableParams(params)) return ReturnType{};
		const auto sdsParams = reinterpret_cast<const ODSParams*>(params);

		std::vector<Real> x{};
		std::vector<std::vector<Real>> Y{ sdsParams->m_functions.size(), std::vector<Real>{} };

		const Real length = sdsParams->m_right_x - sdsParams->m_left_x;
		const Real step = length / sdsParams->m_knotAmount;
		x.push_back(sdsParams->m_left_x);

		for (size_t i = 0; i < sdsParams->m_functions.size(); ++i)
			Y[i].push_back(sdsParams->m_conditions[i]);

		for (size_t i = 1; i <= sdsParams->m_knotAmount; ++i)
		{
			x.push_back(x[i - 1] + step);
			std::vector<Real> k1, k2, k3, k4;
			std::vector<Real> args{};

			std::vector<Real> k2_args(args.size()), k3_args(args.size()), k4_args(args.size());
			const Real xN = x[i - 1];
			
			for (const auto& it : Y)
				args.push_back(it[i - 1]);
			
			for (size_t j = 0; j < sdsParams->m_functions.size(); ++j)
			{	
				k1.push_back(sdsParams->m_functions[j](xN, args));
			}
			std::transform(args.begin(), args.end(), k1.begin(),
				std::back_inserter(k2_args), [step](Real a, Real b) { return a + step * b / 2; });
			
			for (size_t j = 0; j < sdsParams->m_functions.size(); ++j)
			{
				k2.push_back(sdsParams->m_functions[j](xN + step / 2, k2_args));
			}

			std::transform(args.begin(), args.end(), k2.begin(), std::back_inserter(k3_args),
				[step](Real y, Real k) { return y + step * k / 2; });
			
			for (size_t j = 0; j < sdsParams->m_functions.size(); ++j)
			{
				k3.push_back(sdsParams->m_functions[j](xN + step / 2, k3_args));
			}

			std::transform(args.begin(), args.end(), k3.begin(), std::back_inserter(k4_args),
				[step](Real y, Real k) { return y + step * k; });
			
			for (size_t j = 0; j < sdsParams->m_functions.size(); ++j)
			{
				k4.push_back(sdsParams->m_functions[j](xN + step, k3_args));
				Y[j].push_back(Y[j].back() + step * (k1[j] + k2[j] + k3[j] + k4[j]) / 6);
			}
			
			//for (size_t j = 0; j < sdsParams->m_functions.size(); ++j)
			//{

			//}
		}
		Y.insert(Y.begin(), x);
		return Y;
	}
	//------------------------------------------------------------------------------
}