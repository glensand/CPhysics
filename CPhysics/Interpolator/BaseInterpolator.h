#pragma once
#include "IInterpolator.h"

namespace CPhysics
{

class BaseInterpolator : public IInterpolator
{
public:

	BaseInterpolator() = default;
	virtual ~BaseInterpolator() = default;

	bool	SuitableParams(const Params* params) const override;
};

}