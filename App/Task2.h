#pragma once

#include <memory>
#include <cmath>
#include <iostream>
#include <vector>
#include <chrono>
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

	using FX = std::tuple<std::vector<CPhysics::Real>, std::vector<CPhysics::Real>>;
	
	static void	Compute(const std::vector<CPhysics::ISolver*>& solvers, const CPhysics::Params* solverParams, const FX &fx);
	
	static void	Demonstrate(const CPhysics::ByStepResult* inf, const FX &fx);
};
//------------------------------------------------------------------------------
inline void Task2::Run(const Params* params) const
{

	const auto a2 = 1;
	const auto U0 = 2.;
	const auto A = a2 * U0;
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

	CPhysics::Real rightX;
	for(size_t i{ 0 }; ; ++i)
	{
		if (1 - PI * PI * i * i / (a2 * U0) < 0)

		{
			rightX = 1 - PI * PI * (i - 1) * (i - 1) / (a2 * U0);
			break;
		}
	}

	const CPhysics::Real acc{ 0.0001 };
	const CPhysics::OneDimensionalSolverParams d1Params{ acc, .0001, rightX, function1 };

	const auto N = static_cast<size_t>((d1Params.m_rightX - d1Params.m_leftX) / d1Params.m_accuracy);
	std::vector<CPhysics::Real> yXes;
	std::vector<CPhysics::Real> xes;
	yXes.reserve(N);
	xes.reserve(N);

	const auto right = newtonSolver->Solve(&d1Params);
	for(auto x{ 0.01 }; x < right + (rightX - right) / 2; x += d1Params.m_accuracy)
	{
		xes.emplace_back(x);
		yXes.emplace_back(function1(x));
	}
	
	Compute(solvers, &d1Params, {xes, yXes});
}
//------------------------------------------------------------------------------
inline void Task2::Compute(const std::vector<CPhysics::ISolver*>& solvers, const CPhysics::Params* solverParams, const FX &fx)
{
	
	for(const auto &solver : solvers)
	{
		const auto res = solver->SolveByStep(solverParams);

		std::cout << solver->GetSolverType() << ": " << reinterpret_cast<const CPhysics::ByStepD1Result*>(res.get())->m_res << std::endl;
		Demonstrate(res.get(), fx);
	}
}
//------------------------------------------------------------------------------
inline void Task2::Demonstrate(const CPhysics::ByStepResult* inf, const FX& fx)
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

	const auto &[x, y] = fx;
	Plotter::GraphParams graphParams2{ x, y, Plotter::PlotStyle::LINE,
	{ 0, 255, 0 }, "y", 3 };
	
	plot.AddGraph(&graphParams);
	plot.AddGraph(&graphParams2);
	while(true)
	{
		plot.Show();
	}
	
	plot.Close();
}


