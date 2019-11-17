//------------------------------------------------------------------------------
// IDifferentialSystemSolver.h
// Interface for numerical solvers of systems of ordinary differential equations
//
// Copyright (c) 2019 Varumithu
// All rights reserved.
//
// Date: 13.10.2019
// Author: Bachurin Vladimir
//------------------------------------------------------------------------------
#pragma once

#include "../CPhysics.h"

#include <vector>
#include <string>

namespace CPhysics {
	
class IDifferentialSystemSolver
{
public:
	using ReturnType = std::vector<std::vector<Real>>; //[0] is x axis, the rest are
	virtual ~IDifferentialSystemSolver() = default;
	IDifferentialSystemSolver() = default;

	inline virtual bool					SuitableParams(const Params* params) const = 0;
	
	[[nodiscard]] virtual std::string	GetSolverType() const = 0;

	virtual ReturnType					Solve(const Params* params) const = 0;
};

using IDSSolver = IDifferentialSystemSolver;

}

















