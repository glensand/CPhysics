#pragma once

#include <vector>
#include <memory>
#include <cmath>

#include "Facade.h"
#include "TrapezeIntegrator.h"
#include "SimpsonIntegrator.h"

#include "Task.h"

static const double PI{ 3.14 };

class Task4 : public Task
{
public:
	Task4() = default;
	virtual ~Task4() = default;

	void Run() const override
	{
		const std::vector<size_t> intervals = { 4, 16, 32, 64, 128, 256, 512 };

		const auto simpsonIntegrator = std::make_shared<CPhysics::SimpsonIntegrator>();
		const auto trapezeIntegrator = std::make_shared<CPhysics::TrapezeIntegrator>();

		const std::vector<CPhysics::IIntegrator*> integrators = { simpsonIntegrator.get(), trapezeIntegrator.get() };

		const auto function1 = [](CPhysics::Real x)
		{
			const CPhysics::Real x5 = std::pow(x, 5);
			
			return std::sin(PI * x5) / (x5 * (1 - x));
		};

		Facade::Test({ integrators, function1, intervals, "sin(PI * x^5) / (x^5 * (1 - x)", 0, 0, 1 });

		const auto function2 = [](CPhysics::Real x)
		{
			return std::pow(EULER_C, -std::sqrt(x) + std::sin(x / 10));
		};

		Facade::Test({ integrators, function2, intervals, "exp(sqrt(x) + sin(x / 10))", 0, 0, 1 });
	}
	
};