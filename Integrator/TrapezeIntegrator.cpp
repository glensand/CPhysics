#include "TrapezeIntegrator.h"

namespace CPhysics
{
	
Real TrapezeIntegrator::Integrate(Function f, Real leftX, Real rightX, size_t intervals) const
{
	if (!SuitableParams(leftX, rightX, intervals)) return .0;

	const Real dx = (rightX - leftX) / intervals;
	Real result = 0.;
	
	for(size_t i = 0; i< intervals - 1; ++i)
	{
		const Real leftVal = dx * i;
		result += dx * (f(leftVal) + f(leftVal + dx)) / 2;
	}
	
	return result;
}

std::string TrapezeIntegrator::GetIntegratorType() const
{
	return "Trapeze method";
}
}
