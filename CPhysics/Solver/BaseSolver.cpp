#include "BaseSolver.h"

namespace CPhysics
{
bool BaseSolver::SuitableParams(Real leftX, Real rightX) const
{
	return rightX >= leftX;
}
}
