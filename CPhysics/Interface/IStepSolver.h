//------------------------------------------------------------------------------
// IStepSolver.h
//
// IStepSolver implements...
//
// Copyright (c) 2019 GlenSand
// All rights reserved.
//
// Date: dd.mm.2019
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#pragma once

#include "../CPhysics.h"

namespace CPhysics
{
class IStepSolver
{
public:

	IStepSolver() = default;
	virtual ~IStepSolver() = default;

	virtual	ByStepResult	SolveByStep(const Params* params) = 0;
};
}

