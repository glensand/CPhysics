#pragma once

#include <memory>

#include "Task.h"

#include "Solver/DichotomySolver.h"
#include "Solver/SimpleIterationsSolver.h"
#include "Solver/NewtonSolver.h"

class Task2 : public Task
{
	Task2() = default;
	virtual ~Task2() = default;

	void Run(Params* params = nullptr) const override;
}
;

inline void Task2::Run(Params* params) const
{	
	const auto function1 = [](CPhysics::Real x)
	{
		return .0;
	};

	const auto function2 = [](CPhysics::Real x)
	{
		return .0;
	};
	
	const auto simpleIterationsSolver = std::make_shared<CPhysics::SimpleIterationsSolver>();
	const auto newtonSolver = std::make_shared<CPhysics::NewtonSolver>();
	const auto dichotomySolver = std::make_shared<CPhysics::DichotomySolver>();

}

