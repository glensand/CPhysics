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

#include "../CPhysics.h"

#include <vector>
#include <string>

namespace CPhysics {

struct OrdinaryDifferentialSystemParams : Params
{
	size_t m_knot_amount;
	Real m_left_x, m_right_x;
	std::vector<FunctionOfVector> m_functions;
	std::vector<Real> m_conditions; // values of unknowns on the left border, in order of equations	
};

using ODSParams = OrdinaryDifferentialSystemParams;
	
class IDifferentialSystemSolver
{
public:
	using ReturnType = std::vector<std::vector<Real>>; //[0] is x axis, the rest are
	virtual ~IDifferentialSystemSolver() = default;
	IDifferentialSystemSolver() = default;

	inline virtual bool SuitableParams(const Params* params) const;
	[[nodiscard]] virtual std::string	GetSolverType() const = 0;
	virtual ReturnType Solve(const Params* params) const = 0;
};

using IDSSolver = IDifferentialSystemSolver;

bool IDifferentialSystemSolver::SuitableParams(const Params* params) const
{
	const auto odsparams = dynamic_cast<const ODSParams*>(params);
	if (odsparams) return true; //TODO add some checks
	return false;
}

}

















