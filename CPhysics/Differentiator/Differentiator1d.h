//------------------------------------------------------------------------------
// Differentiator1D.h
// General one dimensional integrators abstract class
// Also implements integrators params
//
// Copyright (c) 2019 GlenSand
// All rights reserved.
//
// Date: 27.09.2019
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#pragma once

#include "IDifferentiator.h"

namespace CPhysics
{
//==============================================================================
struct Differentiator1DParams : Params
{
	virtual					~Differentiator1DParams() = default;
	Differentiator1DParams(Real x, Real h, OneDimensionalFunction function)
	:
	m_x(x),
	m_h(h),
	m_function(function)
	{}
	
	Real					m_x{ };
	Real					m_h{ };
	OneDimensionalFunction	m_function{ };
};
//==============================================================================
class Differentiator1D : public IDifferentiator
{
public:
				Differentiator1D() = default;
	
	virtual		~Differentiator1D() = default;

	bool		SuitableParams(const Params* params) const override;

	Real		Differentiate(const Params* params) const override;
};
//==============================================================================
}

