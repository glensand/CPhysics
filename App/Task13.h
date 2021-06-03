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
	void Run(const Params* params = nullptr) override;
};

inline void Task13::Run(const Params* params)
{
	size_t N = 200;

	using Real = CPhysics::Real;
	Real T = 2 * CPhysics::pi;
	Real step = 5 * T / N;
	Real a0 = .1, a1 = 0.002, w0 = 5.1, w1 = 30.1;

	std::vector<Real> y{}, t{}, ftFreq{};
	Real frequency = 2 * CPhysics::pi / step;
	for (size_t i = 0; i < N; ++i)
	{
		t.push_back(step * i);
		y.push_back(a0 * std::sin(t[i] * w0) + a1 * std::sin(t[i] * w1));
		if (i > N / 2)
			ftFreq.push_back((static_cast<double>(i) - (static_cast<double>(N) / 2.)) * frequency / static_cast<double>(N));
	}
	const CPhysics::FFT fft{};
	auto FourierOfY = fft.TransformReal(y);
	std::vector<Real> fourierMag{};

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

	fourierHannaMag.resize(ftFreq.size());
	fourierMag.resize(ftFreq.size());

	const Plotter::GraphParams graphParams1{ ftFreq, fourierMag, Plotter::PlotStyle::POINT_LINE };
	plotter.AddGraph(&graphParams1);

	const Plotter::GraphParams graphParams2{ ftFreq, fourierHannaMag, Plotter::PlotStyle::POINT_LINE };
	plotter.AddGraph(&graphParams2);

	plotter.Show();
	plotter.Close();
}

