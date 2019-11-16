#pragma once
//------------------------------------------------------------------------------
// DichotomySolver.h
// Solve equations using dichotomy method
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

class DichotomySolver : public OneDimensionalSolver
{
public:
	DichotomySolver() = default;
	virtual ~DichotomySolver() = default;

	[[nodiscard]] std::string		GetSolverType() const override;

	Real							Solve(const Params* params) const override;

	std::unique_ptr<ByStepResult>	SolveByStep(const Params* params) const override;
};

}

