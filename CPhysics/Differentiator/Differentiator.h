//------------------------------------------------------------------------------
// DividedDifference.h
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
#include <vector>

namespace CPhysics
{
//==============================================================================
struct DiffParams : Params
{
	virtual					~DiffParams() = default;
	DiffParams(const std::vector<Real> &x, const Function1d &function)
	:
	m_x(x),
	m_function(function)
	{}
	
	std::vector<Real>		m_x{ };
	Function1d				m_function{ };
};
//==============================================================================
class DIfferentiator : public IDifferentiator
{
public:
						DIfferentiator() = default;
	
	virtual				~DIfferentiator() = default;

	bool				SuitableParams(const Params* params) const override;

	std::vector<Real>	Differentiate(const Params* params) const override;
};
//==============================================================================
}

