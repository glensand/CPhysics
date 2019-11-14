#include "FFT.h"
#include <cmath>

namespace CPhysics
{

std::vector<std::complex<CPhysics::Real>> FFT::Transform(const std::vector<std::complex<Real>>& x) const
{
	std::vector<std::complex<CPhysics::Real>> res(x.size());
	const std::complex<double> complex_i(0., 1);
	if (x.size() % 2 == 0)
	{
		std::vector<std::complex<double>> x1(x.size() / 2), x2(x.size() / 2), res(x.size());
		for (size_t i = 0; i < x1.size(); ++i)
		{
			x1[i] = x[2 * i];
			x2[i] = x[2 * i + 1];
		}
		x1 = Transform(x1);
		x2 = Transform(x2);
		for (size_t i = 0; i < x.size() / 2; ++i)
		{
			res[i] = x1[i] + std::exp(-2 * pi * complex_i * static_cast<double>(i) / static_cast<double>(x.size())) * x2[i];
			res[i + x.size() / 2] = x1[i] - std::exp(-2 * pi * complex_i * static_cast<double>(i) / static_cast<double>(x.size()))* x2[i];
		}
		return res;
	}
	else 
	{
		for (size_t i = 0; i < x.size(); ++i)
		{
			for (size_t j = 0; j < x.size(); ++j)
			{
				res[i] += x[j] * std::exp(-2 * pi * complex_i * static_cast<double>(i) * static_cast<double>(j) / static_cast<double>(x.size()));
			}
		}
	}
	
	return res;
}

std::vector<std::complex<CPhysics::Real>> FFT::TransformReal(const std::vector<Real>& x) const
{
	std::vector<std::complex<Real>> res{};
	for (auto& it : x)
	{
		res.emplace_back(it, 0);
	}
	return Transform(res);
}
	
}




