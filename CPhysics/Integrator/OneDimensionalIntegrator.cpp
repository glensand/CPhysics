#include "OneDimensionalIntegrator.h"

namespace
{
const size_t INTERVALS_TO_BE_SMOTH{ 1000 };
}

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
                                         Real leftX, Real rightX, size_t intervals)
{
	if (plotter == nullptr) return;
	
	Plotter::GraphParams graphParams;
	Plotter::GraphParams originalFunctionParams;
	
	graphParams.m_x.reserve(intervals);
	graphParams.m_y.reserve(intervals);

	auto leftVal = leftX;
	const auto dx = (rightX - leftX) / static_cast<Real>(intervals);
	
	for (; leftVal < rightX; leftVal += dx)
	{
		const auto result = function(leftVal);
		
		graphParams.m_x.emplace_back(leftVal);
		graphParams.m_y.emplace_back(result);

		graphParams.m_x.emplace_back(leftVal);
		graphParams.m_y.emplace_back(Real(0));

		graphParams.m_x.emplace_back(leftVal);
		graphParams.m_y.emplace_back(result);
	}

	leftVal = leftX;
	const auto improvedDx = (rightX - leftX) / static_cast<Real>(INTERVALS_TO_BE_SMOTH);
	for(; leftVal < rightX; leftVal += improvedDx)
	{
		originalFunctionParams.m_x.emplace_back(leftVal);
		originalFunctionParams.m_y.emplace_back(function(leftVal));
	}
	
	plotter->AddGraphs(&graphParams);
	plotter->AddGraphs(&originalFunctionParams);
	
	plotter->Show();
}
	
}
