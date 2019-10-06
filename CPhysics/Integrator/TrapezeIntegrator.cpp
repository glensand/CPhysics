#include "TrapezeIntegrator.h"

namespace CPhysics
{
	
Real TrapezeIntegrator::Integrate(const Params* params) const
{
	if (!SuitableParams(params)) return .0;

	const auto oneDimensionalIntegratorParams = reinterpret_cast<const OneDimensionalIntervalsIntegratorParams*>(params);
	Real result = 0.;

	const Real dx = (oneDimensionalIntegratorParams->m_rightX - oneDimensionalIntegratorParams->m_leftX)
		/ Real(oneDimensionalIntegratorParams->m_intervals);
	const auto function = oneDimensionalIntegratorParams->m_function;

	auto leftVal = oneDimensionalIntegratorParams->m_leftX;
	
	for (size_t i{ 0 }; i < oneDimensionalIntegratorParams->m_intervals - 1; ++i, leftVal += dx)
		result += dx * (function(leftVal) + function(leftVal + dx)) / 2;

	{
		const auto trapezeFunction = [function](Real x)
		{
			return function(x);
		};

		visualize(oneDimensionalIntegratorParams->m_plotter, trapezeFunction,
			oneDimensionalIntegratorParams->m_leftX, dx, oneDimensionalIntegratorParams->m_intervals);
	}
	
	return result;
}

std::string TrapezeIntegrator::GetIntegratorType() const
{
	return "Trapeze method";
}

}
