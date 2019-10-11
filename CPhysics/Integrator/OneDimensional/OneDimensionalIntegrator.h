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
struct OneDimensionalIntegratorParams: Params
{
	virtual					~OneDimensionalIntegratorParams() = default;
	OneDimensionalIntegratorParams(Real leftX, Real rightX, OneDimensionalFunction function)
	:
	m_leftX(leftX),
	m_rightX(rightX),
	m_function(function)
	{}
	
	Real					m_leftX{ };
	Real					m_rightX{ };
	OneDimensionalFunction	m_function{ };
};
//==============================================================================
struct OneDimensionalIntervalsIntegratorParams : OneDimensionalIntegratorParams
{
	OneDimensionalIntervalsIntegratorParams(Real leftX, Real rightX, OneDimensionalFunction function, size_t intervals)
	: OneDimensionalIntegratorParams(leftX, rightX, function)
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
