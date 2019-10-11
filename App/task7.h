#pragma once

#include "Task.h"
#include "DifferentialSolver/Euler2Solver.h"
#include "DifferentialSolver/RungeKutta2Solver.h"

#include <iostream>

class Task7 final : public Task
{

	static void print_solution(const CPhysics::Params* params, CPhysics::ISimpleDifferentialSolver* pSolver)
	{
		std::cout << "__________________________________" << std::endl;
		auto res = pSolver->Solve(params);
		for (auto it : res)
		{
			std::cout << it.first << '\t' << it.second << std::endl;
		}
		std::cout << std::endl;
	}
public:
	Task7() = default;
	virtual ~Task7() = default;



	void Run(Params* params = nullptr) const override
	{
		using Real = CPhysics::Real;
		CPhysics::Euler2Params Params(0., 3., 1., 20, 
									[](const Real x, const Real u) { return -u; }, 
									[](const Real x, const Real u) { return 0.0; }, 
									[](const Real x, const Real u) { return -1.; });

		CPhysics::SimpleDifferentialParams rkParams	(0., 3., 1., 20, 
													[](const Real x, const Real u) { return -u; });

		const auto prkParams = reinterpret_cast<CPhysics::Params*>(&rkParams);
		const auto pParams = reinterpret_cast<CPhysics::Params*>(&Params);
		
		CPhysics::Euler2Solver solver;
		CPhysics::RungeKutta2Solver rksolver;
<<<<<<< HEAD

		print_solution(pParams, &solver);
		print_solution(prkParams, &rksolver);
		
=======
		auto rkres = rksolver.Solve(prkParams);
		for (size_t i = 0; i < eres.size(); ++i)
			std::cout << eres[i].first << "\t" << eres[i].second << "\t" << rkres[i].first << "\t" << rkres[i].second << std::endl;	
>>>>>>> 4157781df8189afbb38c6825bfc342ca374e0d25
	}
};