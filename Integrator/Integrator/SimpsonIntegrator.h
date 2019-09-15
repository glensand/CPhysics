#pragma once
#include "BaseIntegrator.h"

namespace CPhysics
{
class SimpsonIntegrator : public BaseIntegrator
{
public:
	
	SimpsonIntegrator() = default;
	virtual ~SimpsonIntegrator() = default;

	Real		Integrate(OneDimensionalFunction f, Real leftX, Real rightX, size_t intervals) const override;

	std::string	GetIntegratorType() const override;
};
}



