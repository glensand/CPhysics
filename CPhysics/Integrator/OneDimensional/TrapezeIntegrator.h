#pragma once
//------------------------------------------------------------------------------
// TrapezeIntegrator.h
// Class implement integration via trapeze method
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
class TrapezeIntegrator : public OneDimensionalIntegrator
{
public:
	TrapezeIntegrator() = default;
	virtual ~TrapezeIntegrator() = default;

	Real							Integrate(const Params* params) const override;

	std::vector<std::vector<Real>>	IntegrationGrid(const Params* params) const override;
	
	[[nodiscard]] std::string		GetIntegratorType() const override;
};

}

