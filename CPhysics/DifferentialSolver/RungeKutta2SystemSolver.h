//------------------------------------------------------------------------------
// SimpleDifferentialSolver.h
// Interface for numerical solvers of systems of ordinary differential equations
//
// Copyright (c) 2019 Varumithu
// All rights reserved.
//
// Date: 13.10.2019
// Author: Bachurin Vladimir
//------------------------------------------------------------------------------
#pragma once

#include "OrdinaryDifferentialSystemSolver.h"

namespace CPhysics {

class RungeKutta2SystemSolver : public OrdinaryDifferentialSystemSolver
{
	
public:
	using ReturnType = std::vector<std::vector<Real>>; //[0] is x axis, the rest are
	virtual ~RungeKutta2SystemSolver() = default;
	RungeKutta2SystemSolver() = default;

	[[nodiscard]] std::string	GetSolverType() const override;

	ReturnType					Solve(const Params* params) const override;
};

using RK2DSSolver = RungeKutta2SystemSolver;
	
}