#include "OrdinaryDifferentialSystemSolver.h"

namespace CPhysics
{
//------------------------------------------------------------------------------
bool OrdinaryDifferentialSystemSolver::SuitableParams(const Params* params) const
{
	const auto systemParams = dynamic_cast<const ODSParams*>(params);
	return systemParams != nullptr; //TODO add some checks
}
//------------------------------------------------------------------------------
}
