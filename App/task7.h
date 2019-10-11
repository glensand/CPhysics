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

	void Run(const Params* params = nullptr) const override;

private:
	static void PrintSolution(const CPhysics::Params* params, CPhysics::ISimpleDifferentialSolver* pSolver);
};

inline void Task7::PrintSolution(const CPhysics::Params* params, CPhysics::ISimpleDifferentialSolver* pSolver)
{
	std::cout << "__________________________________" << std::endl;
	auto res = pSolver->Solve(params);
	for (const auto &it : res)
	{
		std::cout << it.first << '\t' << it.second << std::endl;
	}
	std::cout << std::endl;
}

inline void Task7::Run(const Params* params) const
{
	using Real = CPhysics::Real;
	CPhysics::Euler2Params Params(0., 3., 1., 20,
	                              [](const Real x, const Real u) { return -u; },
	                              [](const Real x, const Real u) { return 0.0; },
	                              [](const Real x, const Real u) { return -1.; });

	CPhysics::SimpleDifferentialParams rkParams(0., 3., 1., 20,
	                                            [](const Real x, const Real u) { return -u; });

	const auto prkParams = reinterpret_cast<CPhysics::Params*>(&rkParams);
	const auto pParams = reinterpret_cast<CPhysics::Params*>(&Params);

	CPhysics::Euler2Solver solver;
	CPhysics::RungeKutta2Solver rksolver;

	PrintSolution(pParams, &solver);
	PrintSolution(prkParams, &rksolver);

	auto rkres = rksolver.Solve(prkParams);
}
