#pragma once
#include "OneDimensionalIntegrator.h"

namespace CPhysics
{
class TrapezeIntegrator : public OneDimensionalIntegrator
{
public:
	TrapezeIntegrator() = default;
	virtual ~TrapezeIntegrator() = default;

	Real Integrate(OneDimensionalFunction f, Real leftX, Real rightX, size_t intervals) const override;

	std::string GetIntegratorType() const override;
};

}

