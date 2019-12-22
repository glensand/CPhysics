#pragma once

#include "ITask.h"
#include "CVPlot/CVPlot.h"
#include "CPhysics.h"
#include "../CPhysics/DifferentialSolver/RungeKutta2SystemSolver.h"
#include "DifferentialSolver/RungeKuttaSystemSolver.h"
#include <iostream>


class bigtask17 : public ITask
{
public:
	bigtask17() = default;
	~bigtask17() = default;

	void Run(const Params* params = nullptr) const override;
};

inline void bigtask17::Run(const Params* params) const
{
	using Real = CPhysics::Real;

	CPhysics::RungeKutta2SystemSolver solver;

	CPhysics::ODSParams odsparams;
	CPhysics::Real E = 0;

	const auto U = [](CPhysics::Real x)
	{
		//return x * x / 2;
		return 0;
	};
	
	odsparams.m_functions = {
								[E, U](Real x, std::vector<Real>& y_vector) { return U(x) * y_vector[1] * 2 - 2 * E * y_vector[1]; },
								[](Real x, std::vector<Real>& y_vector) { return y_vector[0]; }
	};
	odsparams.m_left_x = 0;
	odsparams.m_right_x = CPhysics::pi;
	odsparams.m_knotAmount = 100;
	odsparams.m_conditions = { 1, 0 };

	CPhysics::Real dE = 0.01;
	
	//auto res = solver.Solve(&odsparams);
	auto rk4solver = CPhysics::RungeKuttaSystemSolver();
	auto res = rk4solver.Solve(&odsparams);
	CPhysics::Real prev_diff = std::abs(res[2].back());


	do {
		prev_diff = std::abs(res[2].back());
		E += dE;
		odsparams.m_functions = {
							[E, U](Real x, std::vector<Real>& y_vector) { return U(x) * y_vector[1] * 2 - 2 * E * y_vector[1]; },
							[](Real x, std::vector<Real>& y_vector) { return y_vector[0]; }
		};
		res = rk4solver.Solve(&odsparams);
		std::cout << E << '\t' << res[2].back() << std::endl;
	} while (std::abs(res[2].back()) <= prev_diff);
	E -= dE;
	odsparams.m_functions = {
					[E, U](Real x, std::vector<Real>& y_vector) { return U(x) * y_vector[1] * 2 - 2 * E * y_vector[1]; },
					[](Real x, std::vector<Real>& y_vector) { return y_vector[0]; }
	};
	res = rk4solver.Solve(&odsparams);
	std::cout << E << '\t' << res[2].back() << std::endl;
	//for (size_t i = 0; i < odsparams.m_knotAmount + 1; ++i)
	//{
	//	//for (size_t j = 0; j < odsparams.m_functions.size() + 1; ++j)
	//	//{
	//	//	std::cout << res[j][i] << '\t';
	//	//}

	//	for (size_t j = 0; j < odsparams.m_functions.size() + 1; ++j)
	//	{
	//		std::cout << res2[j][i] << '\t';
	//	}
	//	std::cout << std::endl;
	//}


	
	Plotter::CVPlot plotter;
	Plotter::GraphParams gparams;
	//gparams.m_x = res[0];
	//gparams.m_y = res[2];
	//plotter.AddGraph(&gparams);
	gparams.m_x = res[0];
	gparams.m_y = res[2];
	plotter.AddGraph(&gparams);
	//gparams.m_y = res[2];
	//plotter.AddGraph(&gparams);
	plotter.Show();
	plotter.Close();
}
