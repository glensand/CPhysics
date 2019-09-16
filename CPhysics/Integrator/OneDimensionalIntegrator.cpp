#include "OneDimensionalIntegrator.h"

namespace CPhysics
{
	
bool OneDimensionalIntegrator::SuitableParams(Real leftX, Real rightX, size_t intervals) const
{
	return rightX > leftX && intervals > 0;
}
	
}
