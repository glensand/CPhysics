#include "SimpleDifferentialSolver.h"


namespace CPhysics {

bool ISimpleDifferentialSolver::SuitableParams(const Params* params) const
{
	const auto SDparams = dynamic_cast<const SimpleDifferentialParams*>(params);
	if (SDparams)
		return SDparams->m_rightX >= SDparams->m_leftX;

	return false;

}







	

}