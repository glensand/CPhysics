#include "TrapezeIntegrator.h"

namespace CPhysics
{
//------------------------------------------------------------------------------	
Real TrapezeIntegrator::Integrate(const Params* params) const
{
	if (!SuitableParams(params)) return .0;

	const auto integratorParams = reinterpret_cast<const Integrator1dParamsIntervals*>(params);
	Real result = 0.;

	const Real dx = (integratorParams->m_rightX - integratorParams->m_leftX)
		/ Real(integratorParams->m_intervals);
	const auto function = integratorParams->m_function;

	auto leftVal = integratorParams->m_leftX;
	
	for (size_t i{ 0 }; i < integratorParams->m_intervals; ++i, leftVal += dx)
		result += dx * (function(leftVal) + function(leftVal + dx)) / 2;
	
	return result;
}
//------------------------------------------------------------------------------
std::vector<std::vector<Real>> TrapezeIntegrator::IntegrationGrid(const Params* params) const
{
	if (!SuitableParams(params)) return std::vector<std::vector<Real>>{ };

	const auto integratorParams = reinterpret_cast<const Integrator1dParamsIntervals*>(params);

	std::vector<Real> x, y;
	x.reserve(integratorParams->m_intervals);
	y.reserve(integratorParams->m_intervals);

	auto leftVal = integratorParams->m_leftX;
	const auto dx = (integratorParams->m_rightX - integratorParams->m_leftX)
	/ static_cast<Real>(integratorParams->m_intervals);

	for (; leftVal <= integratorParams->m_rightX + DBL_EPSILON; leftVal += dx)
	{
		const auto result = integratorParams->m_function(leftVal);

		x.emplace_back(leftVal);
		y.emplace_back(result);

		x.emplace_back(leftVal);
		y.emplace_back(Real(0));

		x.emplace_back(leftVal);
		y.emplace_back(result);
	}

	return { x, y };
}
//------------------------------------------------------------------------------
std::string TrapezeIntegrator::GetIntegratorType() const
{
	return "Trapeze method";
}
//------------------------------------------------------------------------------
}
