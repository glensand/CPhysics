#include <vector>
#include <memory>
#include <cmath>
#include <iostream>

#include "Facade.h"
#include "TrapezeIntegrator.h"
#include "SimpsonIntegrator.h"

const double EULER_C{ 2.6 };

int main()
{
	const std::vector<size_t> intervals = { 4, 16, 32, 64, 128, 256, 512 };

	const auto simpsonIntegrator = std::make_shared<CPhysics::SimpsonIntegrator>();
	const auto trapezeIntegrator = std::make_shared<CPhysics::TrapezeIntegrator>();

	const std::vector<CPhysics::IIntegrator*> integrators = { simpsonIntegrator.get(), trapezeIntegrator.get() };

	const auto function1 = [](CPhysics::Real x) { return 1 / (1 + x * x); };

	Facade::Test({ integrators, function1, intervals, "1 / (1 + x^2)", 0, -1, 1 });
	
	const auto function2 = [](CPhysics::Real x) { return std::pow(x, 1 / 3) * std::pow(EULER_C, std::sin(x)); };

	Facade::Test({ integrators, function2, intervals, "x^(1/3) * exp(sin(x))", 0, 0, 1 });

	return 0;
}