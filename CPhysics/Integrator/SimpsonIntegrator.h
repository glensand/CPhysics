#pragma once
#include "OneDimensionalIntegrator.h"

namespace CPhysics
{
class SimpsonIntegrator : public OneDimensionalIntegrator
{
public:
	
	SimpsonIntegrator() = default;
	virtual ~SimpsonIntegrator() = default;

	Real		Integrate(OneDimensionalFunction f, Real leftX, Real rightX, size_t intervals) const override;

	std::string	GetIntegratorType() const override;
};
}



