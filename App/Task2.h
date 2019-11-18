#pragma once

#include <memory>
#include <cmath>
#include <iostream>
#include <vector>

#include <Solver/DichotomySolver.h>
#include <Solver/SimpleIterationsSolver.h>
#include <Solver/NewtonSolver.h>

#include "ITask.h"
#include "CVPlot/CVPlot.h"

class Task2 : public ITask
{
public:
	Task2() = default;
	virtual ~Task2() = default;

	void	Run(const Params* params = nullptr) const override;

private:

	static void	Compute(const std::vector<CPhysics::ISolver*>& solvers, const CPhysics::Params* solverParams);
	
	static void	Demonstrate(const CPhysics::ByStepResult* inf);
};
//------------------------------------------------------------------------------
inline void Task2::Run(const Params* params) const
{
	const auto A = 1.;
	//-------------------------------------------------------
	//		2 * m * a^2 * U0
	// A = --------------------
	//			h^2
	//-------------------------------------------------------
	
	const auto function1 = [A](CPhysics::Real x)
	{
		if (x == 0.) return 0.;
		const auto x1 = std::sqrt(A * (1 - x));
		const auto x2 = std::sqrt(1 / x - 1);
		const auto cTan= 1 / std::tan(x1);
		
		return cTan - x2;
	};
	
	const auto simpleIterationsSolver = std::make_shared<CPhysics::SimpleIterationsSolver>();
	const auto newtonSolver = std::make_shared<CPhysics::NewtonSolver>();
	const auto dichotomySolver = std::make_shared<CPhysics::DichotomySolver>();

	const std::vector<CPhysics::ISolver*> solvers{ simpleIterationsSolver.get(), newtonSolver.get(), dichotomySolver.get() };
	
	const CPhysics::OneDimensionalSolverParams d1Params{0.0001, .0001, .99999, function1 };

	Compute(solvers, &d1Params);
}
//------------------------------------------------------------------------------
inline void Task2::Compute(const std::vector<CPhysics::ISolver*>& solvers, const CPhysics::Params* solverParams)
{
	
	for(const auto &solver : solvers)
	{
		const auto res = solver->SolveByStep(solverParams);

		std::cout << solver->GetSolverType() << ": " << reinterpret_cast<const CPhysics::ByStepD1Result*>(res.get())->m_res << std::endl;
		Demonstrate(res.get());
	}
}
//------------------------------------------------------------------------------
inline void Task2::Demonstrate(const CPhysics::ByStepResult* inf)
{
	const auto& res = dynamic_cast<const CPhysics::ByStepD1Result*>(inf);
	if (res == nullptr) return;

	Plotter::CVPlot plot;

	if (dynamic_cast<const CPhysics::NewtonByStepResult*>(res) != nullptr)
	{
		Plotter::GraphParams newtonGraphParams;

		const auto& newtonRes = dynamic_cast<const CPhysics::NewtonByStepResult*>(res);
		// TODO:: add some related stuff
	}

	Plotter::GraphParams graphParams{ res->m_xs, res->m_ys, Plotter::PlotStyle::POINT,
		{ 0, 0, 255 }, "y", 3 };

	plot.AddGraph(&graphParams);
	plot.Show();
}


