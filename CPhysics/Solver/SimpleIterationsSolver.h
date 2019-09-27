#pragma once
//------------------------------------------------------------------------------
// SimpleIterationSolver.h
// Solve equations with one argument using method
// of simple iterations
//
// Copyright (c) 2019 GlenSand
// All rights reserved.
//
// Date: 27.09.2019
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#include "OneDimensionalSolver.h"

namespace CPhysics
{

class SimpleIterationsSolver : public OneDimensionalSolver
{
public:
	SimpleIterationsSolver() = default;
	virtual ~SimpleIterationsSolver() = default;

	std::string		GetSolverType() const override;

	Real			Solve(const Params* params) const override;

};

}

