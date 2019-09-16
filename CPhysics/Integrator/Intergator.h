#pragma once
#include <string>

#include "..//CPhysics.h"

namespace CPhysics
{
	
class IIntegrator
{
public:

			IIntegrator() = default;
	virtual ~IIntegrator() = default;

	virtual Real			Integrate(const Params* params) const = 0;

	virtual bool			SuitableParams(const Params* params) const = 0;

	virtual std::string		GetIntegratorType() const = 0;
};
}
