#include "OneDimensionalIntegrator.h"

namespace CPhysics
{
//------------------------------------------------------------------------------
bool OneDimensionalIntegrator::SuitableParams(const Params* params) const
{
	const auto integratorParams = dynamic_cast<const Integrator1dParamsIntervals*>(params);
	if (integratorParams == nullptr)
		return false;
	
	return integratorParams->m_rightX > integratorParams->m_leftX
	&& integratorParams->m_intervals > 0;
}
//------------------------------------------------------------------------------	
}
