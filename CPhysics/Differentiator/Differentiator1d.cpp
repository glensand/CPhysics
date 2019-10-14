#include "Differentiator1d.h"

namespace CPhysics
{
//------------------------------------------------------------------------------
bool Differentiator1D::SuitableParams(const Params* params) const
{
	return dynamic_cast<const Differentiator1DParams*>(params) != nullptr;
}
//------------------------------------------------------------------------------
Real Differentiator1D::Differentiate(const Params* params) const
{
	if (!SuitableParams(params)) return Real();

	
	return Real();
}
//------------------------------------------------------------------------------
}
