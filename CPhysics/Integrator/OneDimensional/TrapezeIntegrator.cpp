#include "TrapezeIntegrator.h"

namespace CPhysics
{
//------------------------------------------------------------------------------	
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
	
	return result;
}
//------------------------------------------------------------------------------
std::vector<std::vector<Real>> TrapezeIntegrator::IntegrateByStep(const Params* params) const
{
	if (!SuitableParams(params)) return std::vector<std::vector<Real>>{ };

	const auto oneDimensionalIntegratorParams = reinterpret_cast<const OneDimensionalIntervalsIntegratorParams*>(params);

	std::vector<Real> x, y;
	x.reserve(oneDimensionalIntegratorParams->m_intervals);
	y.reserve(oneDimensionalIntegratorParams->m_intervals);

	auto leftVal = oneDimensionalIntegratorParams->m_leftX;
	const auto dx = (oneDimensionalIntegratorParams->m_rightX - oneDimensionalIntegratorParams->m_leftX)
	/ static_cast<Real>(oneDimensionalIntegratorParams->m_intervals);

	for (; leftVal < oneDimensionalIntegratorParams->m_rightX; leftVal += dx)
	{
		const auto result = oneDimensionalIntegratorParams->m_function(leftVal);

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
