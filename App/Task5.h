#pragma once

#include "ITask.h"
#include <Interpolator/NewtonInterpolator.h>
#include <cmath>
#include <CVPlot/CVPlot.h>

class Task5 final : public ITask
{
public:
	
	Task5() = default;
	virtual ~Task5() = default;

	void Run(const Params* params) const override;
};
//------------------------------------------------------------------------------
inline void Task5::Run(const Params* params = nullptr) const
{
	CPhysics::NewtonInterpolator interpolator;
	const size_t n{ 1000 };
	
	const auto fX = [](CPhysics::Real x)
	{
		return std::log(x);
	};

	std::vector<CPhysics::Real> xes{ };
	xes.reserve(n);
	for(size_t i{ 0 }; i < n; ++i)
		xes.emplace_back(1 + static_cast<CPhysics::Real>(i) / static_cast<CPhysics::Real>(n));
	
	CPhysics::InterpolatorParams interpolatorParams{fX, xes, 3};
	const auto P4 = interpolator.Interpolate(&interpolatorParams);

	const size_t intervals{ 100 };
	const CPhysics::Real rightX{ 2. };
	const CPhysics::Real dx = (rightX - 1) / static_cast<CPhysics::Real>(intervals);

	std::vector<CPhysics::Real> x, y, p4;
	p4.reserve(intervals);
	x.reserve(intervals);
	y.reserve(intervals);

	CPhysics::Real leftX = 1.;
	for(; leftX < rightX; leftX += dx)
	{
		x.emplace_back(leftX);
		p4.emplace_back(P4(leftX) - std::log(leftX));
		y.emplace_back(P4(leftX));
	}
	
	Plotter::CVPlot plot;
	Plotter::GraphParams graphParams1;
	graphParams1.m_x = x;
	graphParams1.m_y = p4;

	Plotter::GraphParams graphParams2;
	graphParams2.m_y = y;
	graphParams2.m_x = x;
	
	plot.AddGraph(&graphParams1);
	plot.AddGraph(&graphParams2);
	
	plot.Show();
}
//------------------------------------------------------------------------------