#pragma once
//------------------------------------------------------------------------------
// SimpsonIntegrator.h
// Implement integration via Simpsons method	
//
// Copyright (c) 2019 GlenSand
// All rights reserved.
//
// Date: 27.09.2019
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#include "OneDimensionalIntegrator.h"

namespace CPhysics
{
class SimpsonIntegrator : public OneDimensionalIntegrator
{
public:
	
	SimpsonIntegrator() = default;
	virtual ~SimpsonIntegrator() = default;

	Real		Integrate(const Params* params) const override;

	std::string	GetIntegratorType() const override;
};
}



