#pragma once
//------------------------------------------------------------------------------
// OneDimensionalSolver.h
// Base class for equation solvers with one argument
//
// Copyright (c) 2019 GlenSand
// All rights reserved.
//
// Date: 27.09.2019
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#include "ISolver.h"

namespace CPhysics
{

struct OneDimensionalSolverParams : Params
{
	Real					m_accuracy{ };
	Real					m_leftX{ };
	Real					m_rightX{ };
	Function1d	m_function{ };
};

class OneDimensionalSolver : public ISolver
{
public:
			OneDimensionalSolver() = default;
	virtual	~OneDimensionalSolver() = default;

	bool	SuitableParams(const Params* params) const override;

};

}
