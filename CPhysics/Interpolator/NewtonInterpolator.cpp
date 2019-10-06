#include "NewtonInterpolator.h"

namespace
{

struct Point final
{
	CPhysics::Real	m_x;
	CPhysics::Real	m_y;
};

void computeXY(const CPhysics::InterpolatorParams* params, std::vector<Point> &points)
{
	points.reserve(params->m_points.size());
	for (size_t i{ 0 }; i < params->m_points.size(); ++i)
	{
		points[i].m_x = params->m_fX(params->m_points[i]);
		points[i].m_y = params->m_fY(params->m_points[i]);
	}
}

}

namespace CPhysics
{

std::vector<Real> NewtonInterpolator::Interpolate(const Params* params) const
{
	if (!SuitableParams(params)) return std::vector<Real>();

	const auto interpolatorParams = reinterpret_cast<const InterpolatorParams*>(params);
	std::vector<Point> points;

	computeXY(interpolatorParams, points);

	
	return std::vector<Real>();
}

std::string NewtonInterpolator::GetInterpolatorType() const
{
	return "Newton interpolation";
}

bool NewtonInterpolator::SuitableParams(const Params* params) const
{
	return BaseInterpolator::SuitableParams(params) && dynamic_cast<const NewtonIterpolatorParams*>(params);
}

}
