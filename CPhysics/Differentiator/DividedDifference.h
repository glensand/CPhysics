//------------------------------------------------------------------------------
// DividedDifference.h
// 
// 
//
// Copyright (c) 2019 GlenSand
// All rights reserved.
//
// Date: 27.09.2019
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#pragma once

#include "IDividedDifference.h"
#include <vector>

namespace CPhysics
{
//==============================================================================
struct DividedDifferenceParams : Params
{
	virtual					~DividedDifferenceParams() = default;
	DividedDifferenceParams(const std::vector<Real> &x, Function1d function, size_t regularity)
	:
	m_x(x),
	m_regularity(regularity),
	m_function(function)
	{}
	
	std::vector<Real>		m_x{ };
	size_t					m_regularity{ };
	Function1d	m_function{ };
};
//==============================================================================
class DividedDifference : public IDividedDifference
{
public:
				DividedDifference() = default;
	
	virtual		~DividedDifference() = default;

	bool		SuitableParams(const Params* params) const override;

	Real		Differentiate(const Params* params) const override;
};
//==============================================================================
}

