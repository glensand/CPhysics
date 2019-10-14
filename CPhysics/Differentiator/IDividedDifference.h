//------------------------------------------------------------------------------
// IDividedDifference.h
// Differentiators interface
//
// Copyright (c) 2019 GlenSand
// All rights reserved.
//
// Date: 27.09.2019
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#pragma once

#include "../CPhysics.h"

namespace CPhysics
{
class IDividedDifference
{
public:

				IDividedDifference() = default;
	virtual		~IDividedDifference() = default;

	virtual Real	Differentiate(const Params* params) const = 0;

	virtual bool	SuitableParams(const Params* params) const = 0;
};
}
