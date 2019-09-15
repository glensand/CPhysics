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

	virtual Real			Integrate(OneDimensionalFunction f, Real leftX, Real rightX, size_t intervals) const = 0;

	virtual bool			SuitableParams(Real leftX, Real rightX, size_t intervals) const = 0;

	virtual std::string		GetIntegratorType() const = 0;
};
}
