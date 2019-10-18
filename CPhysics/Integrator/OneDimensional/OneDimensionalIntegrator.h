//------------------------------------------------------------------------------
// OneDimensionalIntegrator.h
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

#include "../IIntergator.h"

namespace CPhysics
{
//==============================================================================
struct Integrator1dParams: Params
{
	virtual					~Integrator1dParams() = default;
	Integrator1dParams(Real leftX, Real rightX, Function1d function)
	:
	m_leftX(leftX),
	m_rightX(rightX),
	m_function(function)
	{}
	
	Real					m_leftX{ };
	Real					m_rightX{ };
	Function1d				m_function{ };
};
//==============================================================================
struct Integrator1dParamsIntervals : Integrator1dParams
{
	Integrator1dParamsIntervals(Real leftX, Real rightX, Function1d function, size_t intervals)
	: Integrator1dParams(leftX, rightX, function)
	, m_intervals(intervals)
	{}

	size_t	m_intervals{ };
};
//==============================================================================
class OneDimensionalIntegrator : public IIntegrator
{
public:
				OneDimensionalIntegrator() = default;
	
	virtual		~OneDimensionalIntegrator() = default;

	bool		SuitableParams(const Params* params) const override;
};
//==============================================================================
}

