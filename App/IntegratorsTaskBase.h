#pragma once

#include <vector>
#include <Integrator/OneDimensional/OneDimensionalIntegrator.h>
#include <CVPlot/CVPlot.h>

#include "ITask.h"

class IntegratorsTaskBase : public ITask
{
public:
	
				IntegratorsTaskBase() = default;
	virtual		~IntegratorsTaskBase() = default;

protected:
	[[nodiscard]] std::vector<std::vector<double>>	ComputeFunction(const CPhysics::Integrator1dParamsIntervals& params) const;

	void	Demonstrate(const CPhysics::IIntegrator* integrator, const CPhysics::Integrator1dParamsIntervals& params) const;

	const size_t m_analyticalIntervals{ 10000 };
};
//------------------------------------------------------------------------------
inline std::vector<std::vector<double>> IntegratorsTaskBase::ComputeFunction(
	const CPhysics::Integrator1dParamsIntervals& params) const
{
	std::vector<double> x, y;
	x.reserve(params.m_intervals);
	y.reserve(params.m_intervals);

	auto val = params.m_leftX;
	const auto dx = (params.m_rightX - params.m_leftX) / static_cast<double>(m_analyticalIntervals);

	for (; val < params.m_rightX; val += dx)
	{
		x.emplace_back(val);
		y.emplace_back(params.m_function(val));
	}

	return { x, y };
}
//------------------------------------------------------------------------------
inline void IntegratorsTaskBase::Demonstrate(const CPhysics::IIntegrator* integrator,
	const CPhysics::Integrator1dParamsIntervals& params) const
{
	Plotter::CVPlot plot1;
	const auto functionOnGrid = integrator->IntegrationGrid(&params);

	if (functionOnGrid.size() > 1)
	{
		Plotter::GraphParams graphParams;
		graphParams.m_x = functionOnGrid[0];
		graphParams.m_y = functionOnGrid[1];
		graphParams.m_color = { 255, 0,0 };
		plot1.AddGraph(&graphParams);
	}

	const auto analyticalFunction = ComputeFunction(params);
	if (analyticalFunction.size() > 1)
	{
		Plotter::GraphParams graphParams;
		graphParams.m_x = analyticalFunction[0];
		graphParams.m_y = analyticalFunction[1];
		graphParams.m_color = { 0, 0, 255 };
		plot1.AddGraph(&graphParams);
	}

	plot1.Show();
}
//------------------------------------------------------------------------------