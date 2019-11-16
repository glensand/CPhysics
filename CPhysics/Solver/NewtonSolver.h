#pragma once
//------------------------------------------------------------------------------
// NewtonSolver.h
// Solve equations using newton method
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

//==============================================================================
struct NewtonByStepResult : ByStepD1Result
{
	virtual ~NewtonByStepResult() = default;

	std::vector<Real>	m_dy;
};
//==============================================================================
class NewtonSolver : public OneDimensionalSolver
{
public:
	NewtonSolver() = default;
	virtual ~NewtonSolver() = default;

	[[nodiscard]] std::string		GetSolverType() const override;

	Real							Solve(const Params* params) const override;

	std::unique_ptr<ByStepResult>	SolveByStep(const Params* params) const override;
};

}

