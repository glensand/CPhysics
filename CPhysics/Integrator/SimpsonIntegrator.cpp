#include "SimpsonIntegrator.h"

namespace CPhysics
{
Real SimpsonIntegrator::Integrate(const Params* params) const
{
	if (!SuitableParams(params)) return .0;

	const auto oneDimensionalIntegratorParams = reinterpret_cast<const OneDimensionalIntervalsIntegratorParams*>(params);
	Real result = 0.;
	
	const Real dx = (oneDimensionalIntegratorParams->m_rightX - oneDimensionalIntegratorParams->m_leftX)
	/ Real(oneDimensionalIntegratorParams->m_intervals);
	const auto function = oneDimensionalIntegratorParams->m_function;
	
	Real a = oneDimensionalIntegratorParams->m_leftX;
	
	for (size_t i{ 0 }; i < oneDimensionalIntegratorParams->m_intervals - 1; ++i)
	{
		result += function(a) + 4 * function((a + a + dx) / 2) + function(a + dx);
		a += dx;
	}

	{
		const auto simpsonFunction = [dx, function](Real x)
		{
			return function(x) + 4 * function((x + x + dx) / 2) + function(x + dx);
		};

		visualize(oneDimensionalIntegratorParams->m_plotter, simpsonFunction,
			oneDimensionalIntegratorParams->m_leftX, dx, oneDimensionalIntegratorParams->m_intervals);
	}
		
	return result * dx / 6;
}
	
std::string SimpsonIntegrator::GetIntegratorType() const
{
	return "Simpson integrator";
}

};

