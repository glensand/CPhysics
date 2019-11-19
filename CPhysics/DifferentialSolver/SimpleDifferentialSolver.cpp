#include "SimpleDifferentialSolver.h"

namespace CPhysics {

bool ISimpleDifferentialSolver::SuitableParams(const Params* params) const
{
	const auto dParams = dynamic_cast<const SimpleDifferentialParams*>(params);
	if (dParams) return dParams->m_rightX >= dParams->m_leftX;

	return false;
}
}