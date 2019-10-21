#include "Differentiator.h"

namespace CPhysics
{
//------------------------------------------------------------------------------
bool Differentiator::SuitableParams(const Params* params) const
{
	const auto& dVDParams = dynamic_cast<const DiffParams*>(params);
	return (dVDParams != nullptr && dVDParams->m_x.size() > 1);
}
//------------------------------------------------------------------------------
std::vector<Real> Differentiator::Differentiate(const Params* params) const
{
	if (!SuitableParams(params)) return std::vector<Real>();

	const auto dVDParams = reinterpret_cast<const DiffParams*>(params);
	const auto &fx = dVDParams->m_function;
	const auto &x = dVDParams->m_x;
	static const Real h = 10e-5;
	
	std::vector<Real> result;
	result.reserve(x.size());
	for (size_t i{ 0 }; i < x.size(); ++i)
		result.emplace_back((fx(x[i] + h) - fx(x[i] - h)) / (2 * h));

	return result;
}
//------------------------------------------------------------------------------
}
