#pragma once
//------------------------------------------------------------------------------
// NewtonInterpolator.h
// Class implement polynomial interpolation according to Newtons method 
//
// Copyright (c) 2019 GlenSand
// All rights reserved.
//
// Date: 27.09.2019
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#include "BaseInterpolator.h"

namespace CPhysics
{
class  NewtonInterpolator : public BaseInterpolator
{
public:
	
	NewtonInterpolator() = default;
	virtual ~NewtonInterpolator() = default;

	std::function<Real(Real)>	Interpolate(const Params* params) const override;

	[[nodiscard]] std::string	GetInterpolatorType() const override;

	bool						SuitableParams(const Params* params) const override;
};
}