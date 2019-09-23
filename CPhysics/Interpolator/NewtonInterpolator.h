#pragma once
#include "BaseInterpolator.h"

namespace CPhysics
{

struct NewtonIterpolatorParams : InterpolatorParams
{
	NewtonIterpolatorParams(OneDimensionalFunction fx, OneDimensionalFunction fy, 
		const std::vector<size_t> &points, size_t n)
		:
		InterpolatorParams(fx, fy, points),
		m_n(n)
	{}
	
	~NewtonIterpolatorParams() = default;

	size_t	m_n; // Some awesome param, i cant explain
};
	
class  NewtonInterpolator : public BaseInterpolator
{
public:
	
	NewtonInterpolator() = default;
	virtual ~NewtonInterpolator() = default;

	std::vector<Real>	Interpolate(const Params* params) const override;

	std::string			GetInterpolatorType() const override;

	bool				SuitableParams(const Params* params) const override;
};

}