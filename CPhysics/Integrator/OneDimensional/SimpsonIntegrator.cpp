#include "SimpsonIntegrator.h"
#include <functional>

namespace CPhysics
{
//------------------------------------------------------------------------------	
Real SimpsonIntegrator::Integrate(const Params* params) const
{
	if (!SuitableParams(params)) return .0;

	const auto integratorParams = reinterpret_cast<const OneDimensionalIntervalsIntegratorParams*>(params);
	Real result = 0.;
	
	const Real dx = (integratorParams->m_rightX - integratorParams->m_leftX)
	/ Real(integratorParams->m_intervals);
	const auto function = integratorParams->m_function;
	
	Real a = integratorParams->m_leftX;
	
	for (size_t i{ 0 }; i < integratorParams->m_intervals - 1; ++i)
	{
		result += function(a) + 4 * function((a + a + dx) / 2) + function(a + dx);
		a += dx;
	}
		
	return result * dx / 6;
}
//------------------------------------------------------------------------------
std::vector<std::vector<Real>> SimpsonIntegrator::IntegrationGrid(const Params* params) const
{
	if (!SuitableParams(params)) return std::vector<std::vector<Real>>{ };

	const auto integratorParams = reinterpret_cast<const OneDimensionalIntervalsIntegratorParams*>(params);

	const Real h = (integratorParams->m_rightX - integratorParams->m_leftX)
		/ (2 * Real(integratorParams->m_intervals));
	const auto function = integratorParams->m_function;

	Real a = integratorParams->m_leftX;

	std::vector<Real> interpolationX, interpolationY;

	const Real internalIntervals = 20.; // yeeeeeah MOTHERFUCKER
	for (size_t i{ 0 }; i < integratorParams->m_intervals; ++i)
	{
		const Real f0 = function(a);
		const Real f1 = function(a + h);
		const Real f2 = function(a + h + h);
		
		const Real f01 = (f1 - f0) / h;
		const Real f012 = (f0 - 2 * f1 + f2)
			/ (2 * h * h);

		const auto P2 = [f0, f01, f012, a, h](Real x)
		{
			return f0 + f01 * (x - a) + f012 * (x - a) * (x - a - h);
		};

		const Real dx = (h + h) / internalIntervals;
		for(Real x = a; x <= a + h + h; x += dx)
		{
			interpolationY.emplace_back(P2(x));
			interpolationX.emplace_back(x);
		}
		
		a += h + h;
	}

	return {interpolationX, interpolationY};
}
//------------------------------------------------------------------------------
std::string SimpsonIntegrator::GetIntegratorType() const
{
	return "Simpson integrator";
}
//------------------------------------------------------------------------------
};

