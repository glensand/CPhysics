#include "BaseIntegrator.h"

namespace CPhysics
{
	
bool BaseIntegrator::SuitableParams(Real leftX, Real rightX, size_t intervals) const
{
	return rightX > leftX && intervals > 0;
}
	
}
