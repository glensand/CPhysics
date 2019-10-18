#pragma once
//------------------------------------------------------------------------------
// IInterpolator.h
// General polynomial interpolation interface
//
// Copyright (c) 2019 GlenSand
// All rights reserved.
//
// Date: 27.09.2019
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#include "../CPhysics.h"
#include <string>
#include <vector>
#include <functional>

namespace CPhysics
{
//==============================================================================
struct InterpolatorParams : Params
{
	virtual ~InterpolatorParams() = default;

			InterpolatorParams(Function1d fy, const std::vector<Real> &x, size_t n)
				: m_fY(fy)
				, m_x(x)
				, m_n(n)
				{}
		
	Function1d	m_fY{ };	// Function, needs to be interpolated
	std::vector<Real>		m_x;
	size_t					m_n{ };
};
//==============================================================================	
class IInterpolator
{
public:
	IInterpolator() = default;
	virtual ~IInterpolator() = default;

										// Return name of interpolations algorithm 
	virtual std::string					GetInterpolatorType() const = 0;

										// Checkout passed in for compability
	virtual bool						SuitableParams(const Params* params) const = 0;

										// Function interpolation, using points greed
	virtual std::function<Real(Real)>	Interpolate(const Params* params) const = 0;
};
//==============================================================================
}