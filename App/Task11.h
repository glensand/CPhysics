#pragma once

#include "ITask.h"

#include <CVPlot/CVPlot.h>
#include "DifferentialSolver/SpectralProblemSolver.h"
#include <iostream>

class Task11 : public ITask
{
public:

	Task11() = default;
	virtual ~Task11() = default;

	void Run(const Params* params = nullptr) const override;
};

inline void Task11::Run(const Params* params) const
{
	const CPhysics::SpectralProblemSolver solver;

	const auto U = [] ( CPhysics::Real x) -> CPhysics::Real
	{
		return x * x / 2;
	};

	const size_t N{ 60 };
	const size_t n{ 4000 };
	const CPhysics::Real x1{ -10. };
	const CPhysics::Real x2{ 10. };

	std::vector<CPhysics::Real> X;
	X.reserve(n);

	const CPhysics::Real dx = (x2 - x1) / static_cast<CPhysics::Real>(n);
	for (CPhysics::Real x{ x1 }; x < x2; x += dx) X.emplace_back(x);

	const CPhysics::Real dx2 = -1. / (2 * dx * dx);
	std::vector<CPhysics::Real> a(n, dx2);;
	a.front() = 0.;

	std::vector<CPhysics::Real> c(n, dx2);
	c.back() = 0;
	
	std::vector<CPhysics::Real> b;
	b.reserve(n);
	for (size_t i = { 0 }; i < n; ++i) b.emplace_back(1. / (dx * dx) + U(X[i]));
	
	const CPhysics::SpectralProblemSolverParams solverParams{ X,  a, b, c, N, 2};

	const auto result = solver.Solve(&solverParams);
	std::cout << "Energy levels: ";
	std::copy(result[0].begin(), result[0].end(), std::ostream_iterator<CPhysics::Real>(std::cout, " "));
	
	Plotter::CVPlot plot;

	for(size_t i{ 1 }; i < result.size(); ++i)
	{
		Plotter::GraphParams graphParams;
		graphParams.X = X;
		graphParams.Y = result[i];
		
		plot.AddGraph(&graphParams);
	}
	
	plot.Show();
	plot.Close();
}
