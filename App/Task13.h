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
	Real a0 = 1., a1 = 0.1, w0 = 5.1, w1 = 25.5;

	//signal_y = [a0 * math.sin(t * w0) + a1 * math.sin(t * w1) for t in signal_t]
	std::vector<Real> y{}, t{}, ftFreq{};
	Real frequency = 2 * CPhysics::pi / step;
	for (size_t i = 0; i < N; ++i)
	{
		t.push_back(step * i);
		y.push_back(a0 * std::sin(t[i] * w0) + a1 * std::sin(t[i] * w1));
		if (i < N / 2 + 1) {
			ftFreq.push_back(i * frequency / 2);
		}
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
	auto FourierOfSquaredY = fft.Transform(squaredComplex);
	auto FourierOfY = fft.TransformReal(y);
	std::vector<Real> fourierMag{};
	//for (const auto& it : FourierOfSquaredY)
	//{
	//	fourierMag.push_back(abs(it));
	//}

	for (const auto& it : FourierOfY) 
	{
		fourierMag.push_back(abs(it));
	}

	CPhysics::Hanna hanna;
	auto HannaWindow = hanna.Window(N);
	std::vector<Real> YWindowedHanna(y.size());
	for (size_t i = 0; i < N; ++i)
	{
		YWindowedHanna[i] = HannaWindow[i] * y[i];
	}
	auto fourier_hanna = fft.TransformReal(YWindowedHanna);
	std::vector<Real> fourierHannaMag{};
	for (const auto& it : fourier_hanna)
	{
		fourierHannaMag.push_back(abs(it));
	}
	std::vector<Real> fourierHannaMagHalved(N / 2 + 1, 0), fourierMagHalved(N / 2 + 1, 0);
	for (size_t i = 0; i < fourierHannaMagHalved.size(); ++i)
	{
		fourierHannaMagHalved[i] = fourierHannaMag[i];
		fourierMagHalved[i] = fourierMag[i];
	}
	Plotter::CVPlot plotter;
	Plotter::GraphParams graphParams;
	ftFreq.resize(40);
	fourierHannaMag.resize(ftFreq.size());
	fourierMag.resize(ftFreq.size());
	graphParams.m_x = ftFreq;
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

