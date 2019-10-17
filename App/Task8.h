#pragma once
#include "ITask.h"

#include "../CPhysics/DifferentialSolver/RungeKutta2SystemSolver.h"
#include "../CPhysics/DifferentialSolver/OrdinaryDifferentialSystemSolver.h"

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
// Test on one equation
	//CPhysics::ODSParams odsparams;
	//odsparams.m_functions = { [](std::vector<CPhysics::Real> args) { return -args[1]; } };
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
	
	odsparams.m_functions = {
								[](std::vector<CPhysics::Real> args) { return 10. * args[1] - 2. * args[1] * args[2]; },
								[](std::vector<CPhysics::Real> args) { return 2. * args[1] * args[2] - 10. * args[2]; }
							};
	odsparams.m_left_x = 0;
	odsparams.m_right_x = 1;
	odsparams.m_knot_amount = 100;
	odsparams.m_conditions = {10, 100};
	auto res = solver.Solve(&odsparams);
	
	for (size_t i = 0; i < odsparams.m_knot_amount + 1; ++i)
	{
		for (size_t j = 0; j < odsparams.m_functions.size() + 1; ++j)
		{
			std::cout << res[j][i] << '\t';
		}
		std::cout << std::endl;
	}
}
