//------------------------------------------------------------------------------
// ISolver.h
//
// ISolver implements...
//
// Copyright (c) 2019 GlenSand
// All rights reserved.
//
// Date: dd.mm.2019
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#pragma once
#include "../CPhysics.h"
#include <memory>

namespace CPhysics
{
class ISolver
{
public:

	ISolver() = default;
	virtual ~ISolver() = default;

	virtual	Result	Solve(const Params* params) const = 0;

	virtual bool	SuitableParams(const Params* params) const  = 0;

	[[nodiscard]] virtual std::string		GetSolverType() const = 0;
};
}

