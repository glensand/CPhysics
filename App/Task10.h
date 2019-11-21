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

	void Run(const Params* params = nullptr) const override
	{
		using Real = CPhysics::Real;
		Real Pi = CPhysics::pi;
		size_t N = 1000;
		Real delta = Pi / 1000;
		std::vector<Real> a(N - 1, 1.), b(N, -2.), c(N - 1, 1.), d(N, 0);
		b[0] = 1.;
		b[N - 1] = 1.;
		for (size_t i = 0; i < N; ++i)
		{
			d[i] = delta * delta * std::sin(delta * i);
		}
		CPhysics::TridiagonalParams Params;
		Params.a = a;
		Params.b = b;
		Params.c = c;
		Params.d = d;
		CPhysics::TridiagonalSolver solver;
		auto res = solver.Solve(&Params);
		std::vector<Real> x(N, 0);
		for (size_t i = 0; i < N; ++i)
		{
			x[i] = delta * i;
		}
		Plotter::CVPlot plotter;
		Plotter::GraphParams graph_params;
		graph_params.m_style = Plotter::PlotStyle::LINE;
		graph_params.m_x = x;
		graph_params.m_y = res;
		plotter.AddGraph(&graph_params);
		plotter.Show();
	}
};

