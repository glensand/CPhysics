#pragma once

#include "ITask.h"
#include "DifferentialSolver/ImplicitEuler2SystemSolver.h"
#include "../LinearAlgebra/Matrix22.h"

class Task9 : public ITask
{
public:

	Task9() = default;
	virtual ~Task9() = default;

	void Run(const Params* params = nullptr) override;
};
//------------------------------------------------------------------------------	
inline void Task9::Run(const Params* params)
{
	const CPhysics::ImplicitEuler2SystemSolver solver;

	const CPhysics::Real	h{ 0.0001 };
	const size_t			knotAmount{ 100000 };
	const Matrix22			mat22(	1 - h * 998.	,	-1998. * h	,
									h * 999.		,	1 + 1999. * h);
	
	CPhysics::ImplicitEuler2SystemSolverParams iMParams{mat22, 0.9, 0.9, knotAmount};
	
	const auto res = solver.Solve(&iMParams);

	std::vector<CPhysics::Real> xes;
	xes.reserve(knotAmount);
	for(size_t i{ 0 }; i < knotAmount; ++i) xes.emplace_back(static_cast<CPhysics::Real>(i) * h);
	
	Plotter::CVPlot plot;
	Plotter::GraphParams graphParams1{ xes, res[0], Plotter::PlotStyle::POINT_LINE,
		{ 0, 0, 255 }, "y", 1 };

	Plotter::GraphParams graphParams2{ xes, res[1], Plotter::PlotStyle::POINT_LINE,
	{ 0, 255, 0 }, "y", 1 };

	//Plotter::GraphParams graphParams3{ res[0], res[1], Plotter::PlotStyle::POINT_LINE,
	//{ 255, 0, 0 }, "y", 1 };

	plot.AddGraph(&graphParams1);
	plot.AddGraph(&graphParams2);
	//plot.AddGraph(&graphParams3);

	plot.Show();
	plot.Close();
}
