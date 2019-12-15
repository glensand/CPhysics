//------------------------------------------------------------------------------
// ISystemSolver.h
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
class ISystemSolver
{
public:

	ISystemSolver() = default;
	virtual ~ISystemSolver() = default;

	virtual	SystemResult	Solve(const Params* params) = 0;

	
};
}

