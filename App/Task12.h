#pragma once
#include "ITask.h"

#include "DifferentialSolver/CrankNicolsonDiffuseSolver.h"

class Task12 : public ITask
{
public:
	virtual ~Task12() = default;
			Task12() = default;

	void Run(const Params* params = nullptr) const override;
};
//------------------------------------------------------------------------------
inline void Task12::Run(const Params* params) const
{
	const CPhysics::CrankNicolsonDiffuseSolver solver;

	const CPhysics::Real L{ 3. }; // what the fuck?

	const auto func = [=](CPhysics::Real x)
	{
		return x * (1 - x / L) * (1 - x / L);
	};

	const CPhysics::CrankNicolsonDiffuseSolverParams cParams{ func, 0, L, 0.002, 0.1, 3. };

	const auto res = solver.Solve(&cParams);
	__nop();
}
