#include "FFT.h"
#include <cmath>

namespace CPhysics
{

std::vector<std::complex<CPhysics::Real>> FFT::Transform(const std::vector<std::complex<Real>>& x) const
{
	std::vector<std::complex<Real>> res(x.size(), {0., 0.});
	// naive tested
	//for(size_t i{ 0 }; i < res.size(); ++i)
	//{
	//	for (size_t j{ 0 }; j < res.size(); ++j)
	//	{
	//		const auto arg = -2 * pi * i * j / static_cast<Real>(res.size());
	//		res[i] += x[j] * std::complex<Real>{std::cos(arg), std::sin(arg) };
	//	}
	//}

	//return res;
	
	const std::complex<double> cI(0., 1);
	if (x.size() % 2 == 0)
	{
		std::vector<std::complex<Real>> x1(x.size() / 2);
		std::vector<std::complex<Real>> x2(x.size() / 2);
		
		for (size_t i = 0; i < x1.size(); ++i)
		{
			x1[i] = x[2 * i];
			x2[i] = x[2 * i + 1];
		}
		
		x1 = Transform(x1);
		x2 = Transform(x2);

		for (size_t i = 0; i < x.size() / 2; ++i)
		{
			res[i] = x1[i] + std::exp(-2 * pi * cI * static_cast<double>(i) / static_cast<double>(x.size())) * x2[i];
			res[i + x.size() / 2] = x1[i] - std::exp(-2 * pi * cI * static_cast<double>(i) / static_cast<double>(x.size()))* x2[i];
		}
		return res;
	}
	
	for (size_t i = 0; i < x.size(); ++i)
		for (size_t j = 0; j < x.size(); ++j)
		{
			res[i] += x[j] * std::exp(-2 * pi * cI * static_cast<double>(i) * static_cast<double>(j) / static_cast<double>(x.size()));
		}
	
	return res;
}

std::vector<std::complex<CPhysics::Real>> FFT::TransformReal(const std::vector<Real>& x) const
{
	std::vector<std::complex<Real>> res{};
	res.reserve(x.size());
	for (auto& it : x)
		res.emplace_back(it, 0);

	return Transform(res);
}
	
}




