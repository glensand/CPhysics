//------------------------------------------------------------------------------
// IIntegrator.h
// General integrators interface
//
// Copyright (c) 2019 GlenSand
// All rights reserved.
//
// Date: 27.09.2019
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#pragma once

#include <string>

#include "..//CPhysics.h"
#include <vector>

namespace CPhysics
{

class IIntegrator
{
public:

			IIntegrator() = default;
	virtual ~IIntegrator() = default;

	virtual Real							Integrate(const Params* params) const = 0;

	virtual std::vector<std::vector<Real>>	IntegrateByStep(const Params* params) const = 0;

	virtual bool							SuitableParams(const Params* params) const = 0;

	[[nodiscard]] virtual std::string		GetIntegratorType() const = 0;
};
}
