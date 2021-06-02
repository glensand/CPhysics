#pragma once
#include "ITask.h"
#include <vector>
#include <cmath>
#include <CVPlot/CVPlot.h>

class Steering : public ITask
{
public:
	Steering() = default;
	virtual ~Steering() = default;

	void Run(const Params* params) const override;
};

inline void Steering::Run(const Params* params = nullptr) const
{
	const double N{ 2. };
	const double FI_MAX{ 1.3 };
	const double SIN_MAX{ std::sin(FI_MAX) };
	const size_t POINTS{ 100 };
	const double PI{ 3.14 };
	const double K{ SIN_MAX / (PI * N) };
	const double STEP{ PI * 2 * N / static_cast<double>(POINTS) };
	const double LEFT{ -PI * N };

	const auto func = [K](double ksi)
	{
		return std::asin(ksi * K);
	};

	std::vector<double > x, y;
	x.reserve(POINTS);
	y.reserve(POINTS);

	for (double ksi{ LEFT }; ksi < -LEFT; ksi += STEP)
	{
		x.emplace_back(ksi);
		y.emplace_back(func(ksi));
	}

	// normalize
	const auto yMax{ y[y.size() - 1] };
	for (size_t i{ 0 }; i < x.size(); ++i)
	{
		y[i] = y[i] / yMax;
		x[i] = x[i] / (-LEFT);
	}

	Plotter::GraphParams gParams;
	gParams.X = x;
	gParams.Y = y;

	Plotter::CVPlot plot;
	plot.AddGraph(&gParams);

	plot.Show();
}
