#pragma once

#include <vector>
#include <memory>
#include <cmath>

#include "OneDimensionalIntegratorFacade.h"
#include <Integrator/OneDimensional/TrapezeIntegrator.h>
#include <Integrator/OneDimensional/SimpsonIntegrator.h>

#include "IntegratorsTaskBase.h"

static const double PI{ 3.14 };

class Task4 : public IntegratorsTaskBase
{
public:
	Task4() = default;
	virtual ~Task4() = default;

	void Run(const Params* params = nullptr) const override;
};

inline void Task4::Run(const Params* params) const
{
	const std::vector<size_t> intervals = {4, 16, 32, 64, 128, 256, 512};

	const auto simpsonIntegrator = std::make_shared<CPhysics::SimpsonIntegrator>();
	const auto trapezeIntegrator = std::make_shared<CPhysics::TrapezeIntegrator>();

	const std::vector<CPhysics::IIntegrator*> integrators = {simpsonIntegrator.get(), trapezeIntegrator.get()};

	const auto function1 = [](CPhysics::Real x)
	{
		const CPhysics::Real x5 = std::pow(x, 5);

		return std::sin(PI * x5) / (x5 * (1 - x));
	};

	OneDimensionalIntegratorTestParams params1(integrators, intervals, "sin(PI * x^5) / (x^5 * (1 - x)", 0, 0, 1,
	                                           function1);
	OneDimensionalIntegratorFacade::Test(&params1);

	const auto function2 = [](CPhysics::Real x)
	{
		return std::pow(EULER_C, -std::sqrt(x) + std::sin(x / 10));
	};

	OneDimensionalIntegratorTestParams
		params2(integrators, intervals, "exp(sqrt(x) + sin(x / 10))", 0., 0., 1., function2);
	OneDimensionalIntegratorFacade::Test(&params2);

	const CPhysics::OneDimensionalIntervalsIntegratorParams integratorParams1{ 0.01, 0.99, function1, 4 };
	const CPhysics::OneDimensionalIntervalsIntegratorParams integratorParams2{ 0., 1., function2, 4 };

	// demonstration
	Demonstrate(trapezeIntegrator.get(), integratorParams1);
	Demonstrate(simpsonIntegrator.get(), integratorParams1);
	
	Demonstrate(trapezeIntegrator.get(), integratorParams2);
	Demonstrate(simpsonIntegrator.get(), integratorParams2);
}
