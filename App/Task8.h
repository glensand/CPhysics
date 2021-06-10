#pragma once
#include "ITask.h"

#include <DifferentialSolver/RungeKutta2SystemSolver.h>
#include <DifferentialSolver/OrdinaryDifferentialSystemSolver.h>
#include "CVPlot/CVPlot.h"

#include <vector>
#include <iostream>

class Task8 :
	public ITask
{
public:
	Task8() = default;
	virtual ~Task8() = default;

	virtual void Run(const Params * params = nullptr) override;
	virtual void Clear() override {}
};

inline void Task8::Run(const Params* params)
{
	using Real = CPhysics::Real;

	CPhysics::RungeKutta2SystemSolver solver;

	CPhysics::ODSParams odsparams;
	CPhysics::Real a = 10., b = 3., c = 3, d = 10.;
	
	odsparams.m_functions = {
								[a, b](Real x, std::vector<Real>& y_vector) { return a * y_vector[0] - b * y_vector[0] * y_vector[1]; },
								[c, d](Real x, std::vector<Real>& y_vector) { return c * y_vector[0] * y_vector[1] - d * y_vector[1]; }
							};
	odsparams.m_left_x = 0;
	odsparams.m_right_x = 1;
	odsparams.m_knotAmount = 100;
	odsparams.m_conditions = {10, 10};
	auto res = solver.Solve(&odsparams);
	
	for (size_t i = 0; i < odsparams.m_knotAmount + 1; ++i)
	{
		for (size_t j = 0; j < odsparams.m_functions.size() + 1; ++j)
		{
			std::cout << res[j][i] << '\t';
		}
		std::cout << std::endl;
	}

	Plotter::CVPlot plotter;
	Plotter::GraphParameters gparams;
	gparams.X = res[1];
	gparams.Y = res[2];
	plotter.AddGraph(&gparams);
	//gparams.m_y = res[2];
	//plotter.AddGraph(&gparams);
	plotter.Show();
	plotter.Close();
}
