#include "SimpsonIntegrator.h"

namespace CPhysics
{
Real SimpsonIntegrator::Integrate(Function f, Real leftX, Real rightX, size_t intervals) const
{
	if (!SuitableParams(leftX, rightX, intervals)) return .0;

	Real result1 = 0.;
	Real result2 = 0.;

	for (size_t i = 0; i < intervals - 1; i += 2)
	{
		result1 += f(leftX + (rightX - leftX) * (i + 1.0) / (2.0 * intervals));
		result2 += f(leftX + (rightX - leftX) * (i + 2.0) / (2.0 * intervals));
	}

	return (rightX - leftX) * (f(leftX) + f(rightX) + 2 * result2 + 4 * result1) / (6.0 * intervals);
}

std::string SimpsonIntegrator::GetIntegratorType() const
{
	return "Simpson integrator";
}
};

