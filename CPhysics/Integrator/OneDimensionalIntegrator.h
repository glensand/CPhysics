#pragma once
#include "Intergator.h"

namespace CPhysics
{
class OneDimensionalIntegrator : public IIntegrator
{
public:
	OneDimensionalIntegrator() = default;
	
	virtual ~OneDimensionalIntegrator() = default;

	bool SuitableParams(Real leftX, Real rightX, size_t intervals) const override;
};

}

