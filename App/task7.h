#pragma once

#include "Task.h"
#include "DifferentialSolver/Euler2Solver.h"
#include "DifferentialSolver/RungeKutta2Solver.h"

#include <iostream>

class Task7 final : public Task
{
public:
	Task7() = default;
	virtual ~Task7() = default;

	void Run(Params* params = nullptr) const override
	{
		using Real = CPhysics::Real;
		CPhysics::Euler2Params Params;
		Params.m_leftX = 0.;
		Params.m_rightX = 3.;
		Params.m_function = [](const Real x, const Real u) { return -u; };
		Params.m_functionByX = [](const Real x, const Real u) { return 0.0; };
		Params.m_functionByU = [](const Real x, const Real u) { return -1.; };
		Params.m_knotAmount = 20;
		Params.m_leftCond = 1.;

		CPhysics::SimpleDifferentialParams rkParams;
		rkParams.m_leftX = 0.;
		rkParams.m_rightX = 3.;
		rkParams.m_function = [](const Real x, const Real u) { return -u; };
		rkParams.m_knotAmount = 20;
		rkParams.m_leftCond = 1.;

		auto prkParams = reinterpret_cast<CPhysics::Params*>(&rkParams);
		auto pParams = reinterpret_cast<CPhysics::Params*>(&Params);
		
		CPhysics::Euler2Solver solver;
		auto eres = solver.Solve(pParams);
		
		CPhysics::RungeKutta2Solver rksolver;
		auto rkres = rksolver.Solve(prkParams);
		for (size_t i = 0; i < eres.size(); ++i)
			std::cout << eres[i].first << "\t" << eres[i].second << "\t" << rkres[i].first << "\t" << rkres[i].second << std::endl;	
	}
};