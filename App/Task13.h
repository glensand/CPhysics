#pragma once
#include "ITask.h"

#include "../CPhysics/Window/Hanna.h"
#include "../CPhysics/Transform/FFT.h"
#include "CVPlot/CVPlot.h"

class Task13 final :
	public ITask
{
public:
	Task13() = default;
	~Task13() = default;
	void Run(const Params* params = nullptr) const override;
};

inline void Task13::Run(const Params* params) const
{
	size_t N = 1000;

	using Real = CPhysics::Real;
	Real T = 2 * CPhysics::pi;
	Real step = T / N;
	Real a0 = 1., a1 = 0.002, w0 = 5.1, w1 = 25.5;

	//signal_y = [a0 * math.sin(t * w0) + a1 * math.sin(t * w1) for t in signal_t]
	std::vector<Real> y{}, t{};
	for (size_t i = 0; i < N; ++i)
	{
		t.push_back(step * i);
		y.push_back(a0 * std::sin(t[i] * w0) + a1 * std::sin(t[i] * w1));
	}
	std::vector<Real> ySquared{};
	for (auto it : y)
	{
		ySquared.push_back(it * it);
	}
	const CPhysics::FFT fft{};
	std::vector<std::complex<Real>> squaredComplex{};
	for (auto it : ySquared)
	{
		squaredComplex.emplace_back(it, 0);
	}
	auto fourier = fft.Transform(squaredComplex);
	std::vector<Real> fourierMag{};
	for (const auto& it : fourier)
	{
		fourierMag.push_back(abs(it));
	}

	CPhysics::Hanna hanna;
	auto y_squared_hanna = hanna.Window(N);
	for (size_t i = 0; i < N; ++i)
	{
		y_squared_hanna[i] = y_squared_hanna[i] * ySquared[i];
	}
	auto fourier_hanna = fft.TransformReal(y_squared_hanna);
	std::vector<Real> fourierHannaMag{};
	for (auto it : fourier_hanna)
	{
		fourierHannaMag.push_back(abs(it));
	}
	Plotter::CVPlot plotter;
	Plotter::GraphParams graphParams;
	graphParams.m_x = t;
	graphParams.m_y = fourierMag;
	graphParams.m_style = Plotter::PlotStyle::POINT_LINE;
	graphParams.m_pointRadius = 1;
	plotter.AddGraph(&graphParams);
	graphParams.m_y = fourierHannaMag;
	Plotter::Color color;
	color.m_r = 255;
	graphParams.m_color = color;

	plotter.AddGraph(&graphParams);
	plotter.Show();
	plotter.Close();
}

