#pragma once
#include <string>

namespace CPhysics
{

using Real = double;

class IIntegrator
{
public:

	typedef Real(*Function)(Real x);

			IIntegrator() = default;
	virtual ~IIntegrator() = default;

	virtual Real			Integrate(Function f, Real leftX, Real rightX, size_t intervals) const = 0;

	virtual bool			SuitableParams(Real leftX, Real rightX, size_t intervals) const = 0;

	virtual std::string		GetIntegratorType() const = 0;
};
}
