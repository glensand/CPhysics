#pragma once
#include "ITask.h"
#include "CPhysics.h"
#include "SystemSolver/TridiagonalSolver.h"
#include "CVPlot/CVPlot.h"

#include <vector>
#include <cmath>

class Task10 final :
	public ITask
{
public:
	~Task10() = default;
	Task10() = default;

	void Run(const Params* params = nullptr) override
	{
		using Real = CPhysics::Real;

		const Real Pi = CPhysics::pi;
		const size_t N = 100000;
		const Real delta = Pi / N;

		std::vector<Real> a(N, 1.);
		std::vector<Real> b(N, -2.);
		std::vector<Real> c(N, 1.);
		std::vector<Real> d(N, 0);

		a.back() = 0.;
		c.front() = 0.;
		b.front() = 1.;
		b.back() = 1.;

		const Real delta2 = delta * delta;
		for (size_t i = 0; i < N; ++i)
			d[i] = delta2 * std::sin(delta * i);

		d.back() = -2.;
		d[0] = 2;
		CPhysics::TridiagonalParams tridiagonalParams { a, b, c, d};
		
		const CPhysics::TridiagonalSolver solver;
		const auto res = solver.Solve(&tridiagonalParams);

		std::vector<Real> x(N, 0);
		for (size_t i = 0; i < N; ++i)
			x[i] = delta * i;
		
		Plotter::CVPlot plotter;

		Plotter::GraphParams graph_params;
		graph_params.Style = Plotter::PlotStyle::LINE;
		graph_params.X = x;
		graph_params.Y = res;

		plotter.AddGraph(&graph_params);

		plotter.Show();
		plotter.Close();
	}
};

