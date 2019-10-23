#include "Hanna.h"
#include <cmath>

namespace CPhysics
{

std::vector<double> Hanna::Window(const size_t N) const
{
	std::vector<double> res{};
	for (size_t i = 0; i < N; ++i)
	{
		double val = 0.5 * (1 - std::cos((2 * pi * i) / (N - 1)));
		res.push_back(val);
	}
	return res;
}
	
}