#pragma once

#include <vector>
#include <memory>
#include <cmath>

#include "OneDimensionalIntegratorFacade.h"
#include <Integrator/OneDimensional/TrapezeIntegrator.h>
#include <Integrator/OneDimensional/SimpsonIntegrator.h>

#include "IntegratorsTaskBase.h"

class Task4 : public IntegratorsTaskBase
{
public:
	Task4() = default;
	virtual ~Task4() = default;

	void Run(const Params* params = nullptr) override;
};

inline void Task4::Run(const Params* params)
{
	const std::vector<size_t> intervals = { 10000000 };

	const auto simpsonIntegrator = std::make_shared<CPhysics::SimpsonIntegrator>();
	const auto trapezeIntegrator = std::make_shared<CPhysics::TrapezeIntegrator>();

	const std::vector<CPhysics::IIntegrator*> integrators = {simpsonIntegrator.get(), trapezeIntegrator.get()};

	const CPhysics::Real eps{ 10e-9 };
	
	const auto function1 = [=](const CPhysics::Real x) ->CPhysics::Real
	{
		const CPhysics::Real absX{ std::abs(x) };
		if (absX < eps) return PI;
		if (absX < 1 + eps && absX > 1 - eps) return 0;
		
		const CPhysics::Real x5 = std::pow(x, 5);

		return std::sin(PI * x5) / (x5 * (1 - x));
	};

	const OneDimensionalIntegratorTestParams params1(integrators, intervals, "sin(PI * x^5) / (x^5 * (1 - x)", 0, 10 * eps, 1,
	                                           function1);
	OneDimensionalIntegratorFacade::Test(&params1);

	const auto function2 = [](CPhysics::Real x) -> CPhysics::Real
	{
		if (x < 0) return CPhysics::Real(0);
		return std::pow(EULER_C, -std::sqrt(x) + std::sin(x / 10));
	};

	const OneDimensionalIntegratorTestParams
		params2(integrators, intervals, "exp(sqrt(x) + sin(x / 10))", 0., 0., 400., function2);
	OneDimensionalIntegratorFacade::Test(&params2);

	const CPhysics::Integrator1dParamsIntervals integratorParams1{ 0.01, 0.99, function1, 4 };
	const CPhysics::Integrator1dParamsIntervals integratorParams2{ 0., 1., function2, 4 };

	// demonstration
	Demonstrate(trapezeIntegrator.get(), integratorParams1);
	Demonstrate(simpsonIntegrator.get(), integratorParams1);
	
	Demonstrate(trapezeIntegrator.get(), integratorParams2);
	Demonstrate(simpsonIntegrator.get(), integratorParams2);
}
