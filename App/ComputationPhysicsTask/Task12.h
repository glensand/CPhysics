#pragma once
#include "ITask.h"

#include "DifferentialSolver/CrankNicolsonDiffuseSolver.h"
#include <CVPlot/CVPlot.h>

class Task12 : public ITask
{
public:
	virtual ~Task12() = default;
			Task12() = default;

	virtual void Clear() override {}
	void Run(const Params* params = nullptr) override;
};

CPhysics::Real max(const std::vector<CPhysics::Real> &y)
{
	auto maxVal{ DBL_MIN };

	for (size_t i{ 0 }; i < y.size(); ++i)
		if (y[i] > maxVal) maxVal = y[i];

	return maxVal;
}

inline void Task12::Run(const Params* params)
{
	const CPhysics::CrankNicolsonDiffuseSolver solver;

	const CPhysics::Real L{ 3. }; // what the fuck?

	const auto func = [=](CPhysics::Real x)
	{
		return x * (1 - x / L) * (1 - x / L);
	};

	const CPhysics::CrankNicolsonDiffuseSolverParams cParams{ func, 0, L, 0.002, 0.1, 10. };

	const auto res = solver.Solve(&cParams);

	const auto size = static_cast<size_t>((cParams.m_rightX + cParams.m_h) / cParams.m_h);
	std::vector<CPhysics::Real> X;
	std::vector<CPhysics::Real> Y;
	X.reserve(size);
	Y.reserve(size);
	
	for (auto x = cParams.m_leftX; x <= cParams.m_rightX + cParams.m_h; x += cParams.m_h)
		X.emplace_back(x);
	
	for(const auto &v : res)
		Y.emplace_back(max(v));

	Plotter::CVPlot plot;
	const Plotter::GraphParameters graphParams{X, Y};
	
	plot.AddGraph(&graphParams);
	plot.Show();
	plot.Close();
	
}
