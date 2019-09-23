#pragma once
#include "../CPhysics.h"
#include <string>
#include <vector>

namespace CPhysics
{

struct InterpolatorParams : Params
{
	virtual ~InterpolatorParams() = default;

			InterpolatorParams(OneDimensionalFunction fx, OneDimensionalFunction fy, const std::vector<size_t> &points)
				:
				m_fX(fx),
				m_fY(fy),
				m_points(points)
				{}
		
	OneDimensionalFunction	m_fX{ };	// Function, is used for calculate point, to be interpolate in
	OneDimensionalFunction	m_fY{ };	// Function, needs to be interpolated

	std::vector<size_t>		m_points;	// Points set, 0...n ~N
};
	
class IInterpolator
{
public:
	IInterpolator() = default;
	virtual ~IInterpolator() = default;

								// Return name of interpolations algorithm 
	virtual std::string			GetInterpolatorType() const = 0;

								// Checkout passed in for compability
	virtual bool				SuitableParams(const Params* params) const = 0;

								// Function interpolation, using points greed
	virtual std::vector<Real>	Interpolate(const Params* params) const = 0;
};

}