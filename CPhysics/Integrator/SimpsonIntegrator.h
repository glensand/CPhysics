#pragma once
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



