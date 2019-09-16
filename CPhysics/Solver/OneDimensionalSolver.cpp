#include "OneDimensionalSolver.h"

namespace CPhysics
{
bool OneDimensionalSolver::SuitableParams(const Params* params) const
{
	const auto oneDimensionalParams = dynamic_cast<const OneDimensionalParams*>(params);
	if (oneDimensionalParams)
		return oneDimensionalParams->m_rightX >= oneDimensionalParams->m_leftX;

	return false;
}
}
