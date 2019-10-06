#pragma once
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
#include <string>

#include "..//CPhysics.h"

namespace CPhysics
{
	
class IIntegrator
{
public:

			IIntegrator() = default;
	virtual ~IIntegrator() = default;

	virtual Real						Integrate(const Params* params) const = 0;

	virtual bool						SuitableParams(const Params* params) const = 0;

	[[nodiscard]] virtual std::string	GetIntegratorType() const = 0;
};
}
