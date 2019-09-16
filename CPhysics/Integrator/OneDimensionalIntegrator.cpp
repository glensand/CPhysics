#include "OneDimensionalIntegrator.h"

namespace CPhysics
{
	
bool OneDimensionalIntegrator::SuitableParams(const Params* params) const
{
	const auto oneDimensionalIntegratorParams = dynamic_cast<const OneDimensionalIntervalsIntegratorParams*>(params);
	if (oneDimensionalIntegratorParams == nullptr)
		return false;
	
	return oneDimensionalIntegratorParams->m_rightX > oneDimensionalIntegratorParams->m_leftX
	&& oneDimensionalIntegratorParams->m_intervals > 0;
}
	
}
