#pragma once
#include "OneDimensionalIntegrator.h"

namespace CPhysics
{
class TrapezeIntegrator : public OneDimensionalIntegrator
{
public:
	TrapezeIntegrator() = default;
	virtual ~TrapezeIntegrator() = default;

	Real Integrate(const Params* params) const override;

	std::string GetIntegratorType() const override;
};

}

