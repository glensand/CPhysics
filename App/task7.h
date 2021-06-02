#pragma once

#include "ITask.h"
#include "DifferentialSolver/Euler2Solver.h"
#include "DifferentialSolver/RungeKutta2Solver.h"
#include "CVPlot/CVPlot.h"

#include <iostream>
#include <cmath>

class Task7 final : public ITask
{
public:
	Task7() = default;
	virtual ~Task7() = default;

	void Run(const Params* params = nullptr) const override;

private:
	static void PrintSolution(const CPhysics::Params* params, const CPhysics::ISimpleDifferentialSolver* pSolver);
	static std::pair<std::vector<CPhysics::Real>, std::vector<CPhysics::Real>>
		SeparateVectors(const std::vector<CPhysics::Point2D>& vec);

	static std::pair<std::vector<CPhysics::Real>, std::vector<CPhysics::Real>>
		CalculateAnalytical(const size_t knot_amount);
};
//------------------------------------------------------------------------------
inline std::pair<std::vector<CPhysics::Real>, std::vector<CPhysics::Real>>
Task7::CalculateAnalytical(const size_t knot_amount)
{
	std::vector<CPhysics::Real> x{}, y{};
	CPhysics::Real step = 3. / knot_amount;
	for (size_t i = 0; i < knot_amount; ++i)
	{
		x.emplace_back(0 + i * step);
		y.emplace_back(std::exp(- (0 + i * step)));
	}
	return { x, y };
}
//------------------------------------------------------------------------------
inline std::pair<std::vector<CPhysics::Real>, std::vector<CPhysics::Real>> Task7::SeparateVectors(const std::vector<CPhysics::Point2D> &vec)
{
	std::pair<std::vector<CPhysics::Real>, std::vector<CPhysics::Real>> res;
	res.first.reserve(vec.size());
	res.second.reserve(vec.size());
	
	for (const auto &it : vec)
	{
		res.first.emplace_back(it.m_x);
		res.second.emplace_back(it.m_y);
	}
	return res;
}
//------------------------------------------------------------------------------
inline void Task7::PrintSolution(const CPhysics::Params* params, const CPhysics::ISimpleDifferentialSolver* pSolver)
{
	std::cout << "__________________________________" << std::endl;
	auto res = pSolver->Solve(params);
	for (const auto &it : res)
	{
		std::cout << it.m_x << '\t' << it.m_y << std::endl;
	}
	std::cout << std::endl;

	Plotter::CVPlot plot;
	Plotter::GraphParams graph_params1;
	Plotter::GraphParams graph_params2;
	graph_params1.X = SeparateVectors(res).first;
	graph_params1.Y = SeparateVectors(res).second;
	plot.AddGraph(&graph_params1);

	graph_params2.X = CalculateAnalytical(10000).first;
	graph_params2.Y = CalculateAnalytical(10000).second;
	Plotter::Color color;
	color.G = 255;
	graph_params2.Color = color;
	plot.AddGraph(&graph_params2);
	
	plot.Show();
	plot.Close();
}
//------------------------------------------------------------------------------
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

	const CPhysics::Euler2Solver solver;
	const CPhysics::RungeKutta2Solver rksolver;

	PrintSolution(pParams, &solver);
	PrintSolution(prkParams, &rksolver);

	auto rkres = rksolver.Solve(prkParams);
}
