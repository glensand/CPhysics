#pragma once
#include "Intergator.h"

namespace CPhysics
{
class BaseIntegrator : public IIntegrator
{
public:
	BaseIntegrator() = default;
	
	virtual ~BaseIntegrator() = default;

	bool SuitableParams(Real leftX, Real rightX, size_t intervals) const override;
};

}

