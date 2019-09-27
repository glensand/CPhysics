#pragma once
//------------------------------------------------------------------------------
// BaseInterpolator.h
// Base abstract class for all polynomial interpolation classes (at the moment of creation)
//
// Copyright (c) 2019 GlenSand
// All rights reserved.
//
// Date: 27.09.2019
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#include "IInterpolator.h"

namespace CPhysics
{

class BaseInterpolator : public IInterpolator
{
public:

	BaseInterpolator() = default;
	virtual ~BaseInterpolator() = default;

	bool	SuitableParams(const Params* params) const override;
};

}