#include "NewtonInterpolator.h"
#include "../Differentiator/DividedDifference.h"

namespace CPhysics
{
//------------------------------------------------------------------------------
std::function<Real(Real)> NewtonInterpolator::Interpolate(const Params* params) const
{
	if (!SuitableParams(params)) return std::function<Real(Real)>();

	const auto iParams = reinterpret_cast<const InterpolatorParams*>(params);
	const auto &fX = iParams->m_fY;
	const auto &x = iParams->m_x;

	std::vector<Real> coefficients;
	coefficients.reserve(iParams->m_n);

	const DividedDifference difference;
	DividedDifferenceParams dDParams{x, fX, 2};
	
	coefficients.emplace_back(fX(x[0]));
	for(size_t i{ 1 }; i < iParams->m_n; ++i)
	{
		dDParams.m_regularity = i + 1;
		coefficients.emplace_back(difference.Differentiate(&dDParams));
	}

	return [coefficients, x](Real arg)
	{
		Real result{ coefficients[0] };
		for(size_t i{ 1 }; i < coefficients.size(); ++i)
		{
			Real member = coefficients[i];
			
			for (size_t j{ 0 }; j < i; ++j)
				member *= (arg - x[j]);
			
			result += member;
		}
		return result;
	};
}	
//------------------------------------------------------------------------------
std::string NewtonInterpolator::GetInterpolatorType() const
{
	return "Newton interpolation";
}
//------------------------------------------------------------------------------
bool NewtonInterpolator::SuitableParams(const Params* params) const
{
	return BaseInterpolator::SuitableParams(params);
}
//------------------------------------------------------------------------------
}
