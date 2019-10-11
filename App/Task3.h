#pragma once

#include <vector>
#include <memory>
#include <cmath>

#include <Integrator/OneDimensional/TrapezeIntegrator.h>
#include <Integrator/OneDimensional/SimpsonIntegrator.h>
#include <Integrator/OneDimensional/OneDimensionalIntegrator.h>

#include "Task.h"
#include "OneDimensionalIntegratorFacade.h"
#include "CVPlot/CVPlot.h"

class Task3 : public Task
{

public:
	
	Task3() = default;
	virtual  ~Task3() = default;

	void Run(const Params* params = nullptr) const override;

private:

	std::vector<std::vector<double>>	ComputeFunction(const CPhysics::OneDimensionalIntervalsIntegratorParams &params) const;

	const size_t m_analyticalIntervals{ 10000 };	
};
//------------------------------------------------------------------------------
inline std::vector<std::vector<double>> Task3::ComputeFunction(
	const CPhysics::OneDimensionalIntervalsIntegratorParams &params) const
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
inline void Task3::Run(const Params* params) const
{
	const std::vector<size_t> intervals{4, 16, 32, 64, 128, 256, 512};

	const auto simpsonIntegrator = std::make_shared<CPhysics::SimpsonIntegrator>();
	const auto trapezeIntegrator = std::make_shared<CPhysics::TrapezeIntegrator>();

	const std::vector<CPhysics::IIntegrator*> integrators = {simpsonIntegrator.get(), trapezeIntegrator.get()};

	const auto function1 = [](CPhysics::Real x) { return 1 / (1 + x * x); };

	OneDimensionalIntegratorTestParams params1(integrators, intervals, "1 / (1 + x^2)", 0, -1, 1, function1);

	OneDimensionalIntegratorFacade::Test(&params1);

	const auto function2 = [](CPhysics::Real x) { return std::pow(x, 1 / 3) * std::pow(EULER_C, std::sin(x)); };

	OneDimensionalIntegratorTestParams params2(integrators, intervals, "x^(1/3) * exp(sin(x))", 0, 0, 1, function2);
	OneDimensionalIntegratorFacade::Test(&params2);

	CPhysics::OneDimensionalIntervalsIntegratorParams oneDimensionalIntegratorParams1{-1, 1, function1, 4};
	CPhysics::OneDimensionalIntervalsIntegratorParams oneDimensionalIntegratorParams2{0, 1, function2, 4};

	// demonstratinion

	Plotter::CVPlot plot1;
	const auto functionOnGrid = trapezeIntegrator->IntegrateByStep(&oneDimensionalIntegratorParams1);

	if(functionOnGrid.size() > 1)
	{
		Plotter::GraphParams graphParams;
		graphParams.m_x = functionOnGrid[0];
		graphParams.m_y = functionOnGrid[1];
		plot1.AddGraphs(&graphParams);
	}

	const auto analyticalFunction = ComputeFunction(oneDimensionalIntegratorParams1);
	if(analyticalFunction.size() > 1)
	{
		Plotter::GraphParams graphParams;
		graphParams.m_x = analyticalFunction[0];
		graphParams.m_y = analyticalFunction[1];
		plot1.AddGraphs(&graphParams);
	}
	
	plot1.Show();
}
