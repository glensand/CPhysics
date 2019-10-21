//------------------------------------------------------------------------------
// Differentiator.h
// 
// 
//
// Copyright (c) 2019 GlenSand
// All rights reserved.
//
// Date: 17.10.2019
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
class Differentiator : public IDifferentiator
{
public:
						Differentiator() = default;
	
	virtual				~Differentiator() = default;

	bool				SuitableParams(const Params* params) const override;

	std::vector<Real>	Differentiate(const Params* params) const override;
};
//==============================================================================
}

