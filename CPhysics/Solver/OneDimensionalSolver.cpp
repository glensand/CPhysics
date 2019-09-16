#include "OneDimensionalSolver.h"

namespace CPhysics
{
bool OneDimensionalSolver::SuitableParams(SolverParams* params) const
{
	const auto oneDimensionalParams = dynamic_cast<OneDimensionalParams*>(params);
	if (oneDimensionalParams)
		return oneDimensionalParams->m_rightX >= oneDimensionalParams->m_leftX;

	return false;
}
}
