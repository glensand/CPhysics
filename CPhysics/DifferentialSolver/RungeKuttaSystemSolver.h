//------------------------------------------------------------------------------
// RungeKuttaSystemSolver.h
// Uses Runge-Kutta 4th accuracy order method to numerically solve systems of differential equations
//
// Copyright (c) 2019 Varumithu
// All rights reserved.
//
// Date: 17.12.2019
// Author: Bachurin Vladimir
//------------------------------------------------------------------------------
#pragma once

#include "OrdinaryDifferentialSystemSolver.h"

namespace CPhysics {

	class RungeKuttaSystemSolver : public OrdinaryDifferentialSystemSolver
	{

	public:
		using ReturnType = std::vector<std::vector<Real>>; //[0] is x axis, the rest are
		virtual ~RungeKuttaSystemSolver() = default;
		RungeKuttaSystemSolver() = default;

		[[nodiscard]] std::string	GetSolverType() const override;

		ReturnType					Solve(const Params* params) const override;
	};

	using RKDSSolver = RungeKuttaSystemSolver;

}