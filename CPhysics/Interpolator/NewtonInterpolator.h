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

struct NewtonIterpolatorParams : InterpolatorParams
{
	NewtonIterpolatorParams(OneDimensionalFunction fx, OneDimensionalFunction fy, 
		const std::vector<size_t> &points, size_t n)
		:
		InterpolatorParams(fx, fy, points),
		m_n(n)
	{}
	
	~NewtonIterpolatorParams() = default;

	size_t	m_n; // Some awesome param, i cant explain
};
	
class  NewtonInterpolator : public BaseInterpolator
{
public:
	
	NewtonInterpolator() = default;
	virtual ~NewtonInterpolator() = default;

	std::vector<Real>	Interpolate(const Params* params) const override;

	std::string			GetInterpolatorType() const override;

	bool				SuitableParams(const Params* params) const override;
};

}