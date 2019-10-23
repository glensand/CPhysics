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
	void Run(const Params* params = nullptr) const override
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
		std::vector<Real> y_squared{};
		for (auto it : y)
		{
			y_squared.push_back(it * it);
		}
		const CPhysics::FFT fft{};
		std::vector<std::complex<Real>> y_squared_complex{};
		for (auto it : y_squared)
		{
			y_squared_complex.emplace_back(it, 0);
		}
		auto fourier = fft.Transform(y_squared_complex);
		std::vector<Real> fourier_mag{};
		for (auto it : fourier)
		{
			fourier_mag.push_back(abs(it));
		}
		CPhysics::Hanna hanna;
		auto y_squared_hanna = hanna.Window(N);
		for (size_t i = 0; i < N; ++i)
		{
			y_squared_hanna[i] = y_squared_hanna[i] * y_squared[i];
		}
		auto fourier_hanna = fft.TransformReal(y_squared_hanna);
		std::vector<Real> fourier_hanna_mag{};
		for (auto it : fourier_hanna)
		{
			fourier_hanna_mag.push_back(abs(it));
		}
		Plotter::CVPlot plotter;
		Plotter::GraphParams gparams;
		gparams.m_x = t;
		gparams.m_y = fourier_mag;
		plotter.AddGraph(&gparams);
		gparams.m_y = fourier_hanna_mag;
		plotter.AddGraph(&gparams);
		plotter.Show();
	}
};

