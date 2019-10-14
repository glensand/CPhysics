#include "DividedDifference.h"

namespace CPhysics
{
//------------------------------------------------------------------------------
bool DividedDifference::SuitableParams(const Params* params) const
{
	const auto& dVDParams = dynamic_cast<const DividedDifferenceParams*>(params);
	return (dVDParams != nullptr && dVDParams->m_x.size() > 1);
}
//------------------------------------------------------------------------------
Real DividedDifference::Differentiate(const Params* params) const
{
	if (!SuitableParams(params)) return Real();

	const auto dVDParams = reinterpret_cast<const DividedDifferenceParams*>(params);
	const auto &fx = dVDParams->m_function;
	const size_t regularity = dVDParams->m_regularity;
	const auto &x = dVDParams->m_x;
	
	Real result{ .0 };
	for (size_t i{ 0 }; i < regularity; ++i)
	{
		Real divider{ 1. };
		for(size_t j = 0; j < regularity; ++j)
		{
			if (i != j)
				divider *= (x[i] - x[j]);
		}

		result += fx(x[i]) / divider;
	}
	
	return result;
}
//------------------------------------------------------------------------------
}
