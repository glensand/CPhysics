//------------------------------------------------------------------------------
// ITransform.h
// Interface for transforms of vectors of complex numbers
//
// Copyright (c) 2019 Varumithu
// All rights reserved.
//
// Date: 22.10.2019
// Author: Bachurin Vladimir
//------------------------------------------------------------------------------

#pragma once

#include "../CPhysics.h"

#include <complex>

namespace CPhysics
{

class ITransform
{
public:
	ITransform() = default;
	virtual ~ITransform() = default;

	virtual std::vector<std::complex<Real>> Transform(const std::vector<std::complex<Real>>& x) const = 0;
	virtual std::vector<std::complex<Real>> TransformReal(const std::vector<Real>& x) const = 0;
};

};