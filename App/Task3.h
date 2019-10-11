#pragma once

#include <vector>
#include <memory>
#include <cmath>

#include <Integrator/TrapezeIntegrator.h>
#include <Integrator/SimpsonIntegrator.h>
#include <Integrator/OneDimensionalIntegrator.h>

#include "Task.h"
#include "OneDimensionalIntegratorFacade.h"
#include "CVPlot/CVPlot.h"

class Task3 : public Task
{

public:
	
	Task3() = default;
	virtual  ~Task3() = default;

	void Run(Params* params = nullptr) const override
	{
		const std::vector<size_t> intervals { 4, 16, 32, 64, 128, 256, 512 };

		const auto simpsonIntegrator = std::make_shared<CPhysics::SimpsonIntegrator>();
		const auto trapezeIntegrator = std::make_shared<CPhysics::TrapezeIntegrator>();

		const std::vector<CPhysics::IIntegrator*> integrators = { simpsonIntegrator.get(), trapezeIntegrator.get() };

		const auto function1 = [](CPhysics::Real x) { return 1 / (1 + x * x); };

		OneDimensionalIntegratorTestParams params1(integrators, intervals, "1 / (1 + x^2)", 0, -1, 1, function1);
			
		OneDimensionalIntegratorFacade::Test(&params1);

		const auto function2 = [](CPhysics::Real x) { return std::pow(x, 1 / 3) * std::pow(EULER_C, std::sin(x)); };

		OneDimensionalIntegratorTestParams params2(integrators, intervals, "x^(1/3) * exp(sin(x))", 0, 0, 1, function2);
		OneDimensionalIntegratorFacade::Test(&params2);

		CPhysics::OneDimensionalIntervalsIntegratorParams oneDimensionalIntegratorParams1{-1, 1, function1, 4};
		CPhysics::OneDimensionalIntervalsIntegratorParams oneDimensionalIntegratorParams2{0, 1, function2, 4};

		// demonstratinion
		{
			Plotter::CVPlot plot1;
			Plotter::CVPlot plot2;

			oneDimensionalIntegratorParams1.m_plotter = reinterpret_cast<Plotter::IPlot*>(&plot1);
			oneDimensionalIntegratorParams2.m_plotter = reinterpret_cast<Plotter::IPlot*>(&plot2);

			const auto unUsed = trapezeIntegrator->Integrate(&oneDimensionalIntegratorParams1);
		}
	}
};
