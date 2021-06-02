#pragma once

#include "ITask.h"
#include <Integrator/OneDimensional/SimpsonIntegrator.h>
#include <Integrator/OneDimensional/TrapezeIntegrator.h>
#include <Differentiator/Differentiator.h>

#include <vector>
#include <functional>
#include <cmath>
#include <iostream>
#include <fstream>

#include <CVPlot/CVPlot.h>

#define  _HALF_DEBUG

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
	
	static void DebugPrint(const std::vector<CPhysics::Real>& x, const std::vector<CPhysics::Real>& y, const std::string& outputFileName) noexcept;
	
	static void DebugPrint(const std::vector<CPhysics::Real>&, const std::string& outputFileName) noexcept;

	static void Render(const std::vector<CPhysics::Real>& x, const std::vector<CPhysics::Real>& y1, const std::vector<CPhysics::Real>& y2) noexcept;
};
//------------------------------------------------------------------------------
inline void Task6::Run(const Params* params) const
{
	//CPhysics::SimpsonIntegrator integrator;
	CPhysics::TrapezeIntegrator	integrator;
	
	const auto J0 = GetBessel(0, &integrator);
	const auto J1 = GetBessel(1, &integrator);

	const CPhysics::Real leftX{ 0 };
	CPhysics::Real x{ leftX };
	const CPhysics::Real rightX{ 2 * 3.141592653589793238463 };
	const size_t intervals{ 100 };
	const CPhysics::Real dx = (rightX - leftX) / static_cast<CPhysics::Real>(intervals);

	std::vector<CPhysics::Real> xes;
	xes.reserve(intervals);
	for (; x < rightX; x += dx) xes.emplace_back(x);
	
	const auto vectorJ1 = ComputeJ(J1, xes);
	const auto vectorDJ0 = ComputeDJDX(J0, xes);

#ifdef  _HALF_DEBUG
	const auto debVec = ComputeJ(J0, xes);
	DebugPrint(xes, vectorJ1, "J1.csv");
	DebugPrint(xes, debVec, "J0.csv");
	DebugPrint(xes, "xes.csv");

	Render(xes, vectorJ1, vectorDJ0);

#endif

	const CPhysics::Real delta = 10e-10;

	for(size_t i{ 0 }; i < vectorDJ0.size() && i < vectorJ1.size(); ++i)
	{
		const auto diff{ std::abs(vectorJ1[i] + vectorDJ0[i]) };

		if (diff > delta)
		{
			std::cout << i << ": wrong " << diff << std::endl;
			break;
		}
		
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
	const CPhysics::Differentiator differentiator;
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
		const CPhysics::Real PI{ 3.141592653589793238463 };
		CPhysics::Integrator1dParamsIntervals params{ 0, PI, j, 100 };
		
		return integrator->Integrate(&params) / PI;
	};
}
//------------------------------------------------------------------------------
inline void Task6::DebugPrint(const std::vector<CPhysics::Real>& x, const std::vector<CPhysics::Real>& y, const std::string& outputFileName) noexcept
{
	std::ofstream out(outputFileName);

	for(size_t i{ 0 }; i < x.size() && i < y.size(); ++i)
		out << x[i] << " " << y[i] << std::endl;
}
//------------------------------------------------------------------------------
inline void Task6::DebugPrint(const std::vector<CPhysics::Real>& y, const std::string& outputFileName) noexcept
{
	std::ofstream out(outputFileName);

	for (size_t i{ 0 }; i < y.size(); ++i)
		out << y[i] << std::endl;
}
//------------------------------------------------------------------------------
inline void Task6::Render(const std::vector<CPhysics::Real>& x, const std::vector<CPhysics::Real>& y1,
	const std::vector<CPhysics::Real>& y2) noexcept
{
	Plotter::CVPlot plot;
	
	Plotter::GraphParams params1;
	params1.Color = { 255, 0, 0 };
	params1.X = x;
	params1.Y = y2;

	Plotter::GraphParams params2;
	params2.Color = { 0, 255, 0 };
	params2.X = x;
	params2.Y = y1;

	plot.AddGraph(&params2);
	plot.AddGraph(&params1);
	plot.Show();
	plot.Close();
}
//------------------------------------------------------------------------------