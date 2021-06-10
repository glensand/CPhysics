#pragma once

#include <vector>
#include <memory>
#include <cmath>

#include <Integrator/OneDimensional/TrapezeIntegrator.h>
#include <Integrator/OneDimensional/SimpsonIntegrator.h>
#include <Integrator/OneDimensional/OneDimensionalIntegrator.h>

#include "IntegratorsTaskBase.h"
#include "OneDimensionalIntegratorFacade.h"
#include "CVPlot/CVPlot.h"

class Task3 : public IntegratorsTaskBase
{

public:
	
	Task3() = default;
	virtual  ~Task3() = default;

	void Run(const Params* params = nullptr) override;
	virtual void Clear() override {}
};

inline void Task3::Run(const Params* params)
{
	const std::vector<size_t> intervals{4, 16, 32, 64, 128, 256, 512};

	const auto simpsonIntegrator = std::make_shared<CPhysics::SimpsonIntegrator>();
	const auto trapezeIntegrator = std::make_shared<CPhysics::TrapezeIntegrator>();

	const std::vector<CPhysics::IIntegrator*> integrators = {simpsonIntegrator.get(), trapezeIntegrator.get()};

	const auto function1 = [](CPhysics::Real x) { return 1 / (1 + x * x); };

	OneDimensionalIntegratorTestParams params1(integrators, intervals, "1 / (1 + x^2)", 0, -1, 1, function1);

	OneDimensionalIntegratorFacade::Test(&params1);

	const auto function2 = [](CPhysics::Real x) { return std::pow(x, 1.0 / 3.0) * std::pow(EULER_C, std::sin(x)); };

	OneDimensionalIntegratorTestParams params2(integrators, intervals, "x^(1/3) * exp(sin(x))", 0, 0, 1, function2);
	OneDimensionalIntegratorFacade::Test(&params2);

	const CPhysics::Integrator1dParamsIntervals integratorParams1{-1, 1, function1, 4};
	const CPhysics::Integrator1dParamsIntervals integratorParams2{0, 1, function2, 4};

	// demonstration
	Demonstrate(trapezeIntegrator.get(), integratorParams1);
	Demonstrate(trapezeIntegrator.get(), integratorParams2);

	Demonstrate(simpsonIntegrator.get(), integratorParams1);
	Demonstrate(simpsonIntegrator.get(), integratorParams2);
}
