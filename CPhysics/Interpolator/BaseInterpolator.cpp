#include "BaseInterpolator.h"

namespace CPhysics
{
//------------------------------------------------------------------------------
bool BaseInterpolator::SuitableParams(const Params* params) const
{
	return dynamic_cast<const InterpolatorParams*>(params) != nullptr;
}
//------------------------------------------------------------------------------
}
