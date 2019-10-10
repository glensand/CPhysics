#include "OneDimensionalIntegrator.h"

namespace CPhysics
{

bool OneDimensionalIntegrator::SuitableParams(const Params* params) const
{
	const auto oneDimensionalIntegratorParams = dynamic_cast<const OneDimensionalIntervalsIntegratorParams*>(params);
	if (oneDimensionalIntegratorParams == nullptr)
		return false;
	
	return oneDimensionalIntegratorParams->m_rightX > oneDimensionalIntegratorParams->m_leftX
	&& oneDimensionalIntegratorParams->m_intervals > 0;
}

void OneDimensionalIntegrator::visualize(Plotter::IPlot* plotter, const std::function<Real(Real)>& function,
                                         Real leftX, Real dx, size_t intervals)
{
	if (plotter == nullptr) return;
	
	Plotter::GraphParams plotParams;
	Plotter::GraphParams info;

	info.m_x.reserve(intervals);
	info.m_y.reserve(intervals);

	auto leftVal = leftX;
	for (size_t i{ 0 }; i < intervals - 1; ++i, leftVal += dx)
	{
		info.m_x.emplace_back(leftVal);
		info.m_y.emplace_back(function(leftVal));
	}

	plotter->AddGraphs(&plotParams);
}
	
}
