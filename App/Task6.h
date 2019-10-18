#pragma once

#include "ITask.h"
#include <Integrator/OneDimensional/SimpsonIntegrator.h>
#include <Integrator/OneDimensional/TrapezeIntegrator.h>
#include <Differentiator/Differentiator.h>

#include <vector>
#include <functional>
#include <cmath>
#include <iostream>

class Task6 : public ITask
{
public:
	Task6() = default;
	~Task6() = default;

	void Run(const Params* params = nullptr) const override;

private:

	static std::vector<CPhysics::Real> ComputeJ(const CPhysics::Function1d& J, const std::vector<CPhysics::Real>& xes);

	static std::vector<CPhysics::Real> ComputeDJDX(const CPhysics::Function1d& J, const std::vector<CPhysics::Real>& xes);
	
	static CPhysics::Function1d GetBessel(size_t m, const CPhysics::IIntegrator* integrator);
};
//------------------------------------------------------------------------------
inline void Task6::Run(const Params* params) const
{
	CPhysics::SimpsonIntegrator simpsonIntegrator;
	
	const auto J0 = GetBessel(0, &simpsonIntegrator);
	const auto J1 = GetBessel(1, &simpsonIntegrator);

	const CPhysics::Real leftX{ 0 };
	CPhysics::Real x{ leftX };
	const CPhysics::Real rightX{ 2 * 3.14 };
	const size_t intervals{ 10000 };
	const CPhysics::Real dx = (rightX - leftX) / static_cast<CPhysics::Real>(intervals);

	std::vector<CPhysics::Real> xes;
	xes.reserve(intervals);
	for (; x < rightX; x += dx) xes.emplace_back(x);
	
	const auto vectorJ1 = ComputeJ(J1, xes);
	const auto vectorDJ0 = ComputeDJDX(J0, xes);

	const CPhysics::Real delta = 2e-10;

	for(size_t i{ 0 }; i < vectorDJ0.size() && i < vectorJ1.size(); ++i)
		if(std::abs(vectorJ1[i] - vectorDJ0[i]) > delta)
		{
			std::cout << "wrong" << std::endl;
			break;
		}
}
//------------------------------------------------------------------------------
inline std::vector<CPhysics::Real> Task6::ComputeJ(const CPhysics::Function1d& J, const std::vector<CPhysics::Real> &xes)
{
	std::vector<CPhysics::Real> y;
	y.reserve(xes.size());
	for (const auto &x : xes)
		y.emplace_back(J(x));

	return y;
}
//------------------------------------------------------------------------------
inline std::vector<CPhysics::Real> Task6::ComputeDJDX(const CPhysics::Function1d& J, const std::vector<CPhysics::Real>& xes)
{
	const CPhysics::DIfferentiator differentiator;
	const CPhysics::DiffParams params {xes, J};

	return differentiator.Differentiate(&params);
}
//------------------------------------------------------------------------------
inline CPhysics::Function1d Task6::GetBessel(size_t m, const CPhysics::IIntegrator *integrator)
{
	return [m, integrator](CPhysics::Real x)
	{
		const auto j = [x, m](CPhysics::Real t)
		{
			return std::cos(m * t - x * std::sin(t));
		};
		const CPhysics::Real PI{ 3.14 };
		CPhysics::Integrator1dParamsIntervals params{ 0, PI, j, 10000 };
		
		return integrator->Integrate(&params) / PI;
	};
}
//------------------------------------------------------------------------------