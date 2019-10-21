#pragma once
#include "ITask.h"

#include "../CPhysics/DifferentialSolver/RungeKutta2SystemSolver.h"
#include "../CPhysics/DifferentialSolver/OrdinaryDifferentialSystemSolver.h"
#include "CVPlot/CVPlot.h"

#include <vector>
#include <iostream>

class Task8 :
	public ITask
{
public:
	Task8() = default;
	virtual ~Task8() = default;

	inline void Run(const Params * params = nullptr) const override;
};

inline void Task8::Run(const Params* params) const
{
	using Real = CPhysics::Real;
// Test on one equation
	//CPhysics::ODSParams odsparams;
	//odsparams.m_functions = { [](std::vector<CPhysics::Real> y_vector) { return -y_vector[1]; } };
	//odsparams.m_conditions = { 1 };
	//odsparams.m_left_x = 0;
	//odsparams.m_right_x = 3;
	//odsparams.m_knot_amount = 20;

	CPhysics::RungeKutta2SystemSolver solver;
	//auto res = solver.Solve(&odsparams);
	//for (size_t i = 0; i < 20; ++i)
	//{
	//	std::cout << res[0][i] << '\t' << res[1][i] << std::endl;
	//}
	CPhysics::ODSParams odsparams;
	CPhysics::Real a = 10., b = 2., c = 2., d = 10.;
	
	odsparams.m_functions = {
								[a, b](Real x, std::vector<Real>& y_vector) { return a * y_vector[0] - b * y_vector[0] * y_vector[1]; },
								[c, d](Real x, std::vector<Real>& y_vector) { return c * y_vector[0] * y_vector[1] - d * y_vector[1]; }
							};
	odsparams.m_left_x = 0;
	odsparams.m_right_x = 1;
	odsparams.m_knot_amount = 100;
	odsparams.m_conditions = {10, 10};
	auto res = solver.Solve(&odsparams);
	
	for (size_t i = 0; i < odsparams.m_knot_amount + 1; ++i)
	{
		for (size_t j = 0; j < odsparams.m_functions.size() + 1; ++j)
		{
			std::cout << res[j][i] << '\t';
		}
		std::cout << std::endl;
	}

	Plotter::CVPlot plotter;
	Plotter::GraphParams gparams;
	gparams.m_x = res[0];
	gparams.m_y = res[1];
	plotter.AddGraph(&gparams);
	gparams.m_y = res[2];
	plotter.AddGraph(&gparams);
	plotter.Show();
}
