#include "SimpsonIntegrator.h"

namespace CPhysics
{
Real SimpsonIntegrator::Integrate(OneDimensionalFunction f, Real leftX, Real rightX, size_t intervals) const
{
	if (!SuitableParams(leftX, rightX, intervals)) return .0;

	Real result = 0.;
	const Real dx = (rightX - leftX) / (Real(intervals));
	Real a = leftX;
	
	for (size_t i = 0; i < intervals - 1; ++i)
	{
		result += f(a) + 4 * f((a + a + dx) / 2) + f(a + dx);
		a += dx;
	}

	return result * dx / 6;
}
	
std::string SimpsonIntegrator::GetIntegratorType() const
{
	return "Simpson integrator";
}
};

