//------------------------------------------------------------------------------
// RungeKutta2Solver.h
// Numerical soler of ordinary differential equations by
// Runge-Kutta's second order of precision method
//
// Copyright (c) 2019 Varumithu
// All rights reserved.
//
// Date: 10.10.2019
// Author: Bachurin Vladimir
//------------------------------------------------------------------------------

#pragma once

#include "SimpleDifferentialSolver.h"

namespace CPhysics
{

class RungeKutta2Solver final : public ISimpleDifferentialSolver
{
public:
	RungeKutta2Solver() = default;
	virtual	~RungeKutta2Solver() = default;

	std::string		GetSolverType() const override;
	bool	SuitableParams(const Params * params) const override;
	std::vector<std::pair<Real, Real>> Solve(const Params * params) const override;
};
	
}