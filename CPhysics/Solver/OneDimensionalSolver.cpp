#include "OneDimensionalSolver.h"

namespace CPhysics
{
//------------------------------------------------------------------------------
bool OneDimensionalSolver::SuitableParams(const Params* params) const
{
	const auto solverParams = dynamic_cast<const OneDimensionalSolverParams*>(params);
	if (solverParams)
		return solverParams->m_rightX >= solverParams->m_leftX;

	return false;
}
//------------------------------------------------------------------------------
}
