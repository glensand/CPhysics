#include "Hanna.h"
#include <cmath>

namespace CPhysics
{
std::vector<Real> Hanna::Window(const size_t N) const
{
	std::vector<double> res{};
	res.reserve(N);
	for (size_t i = 0; i < N; ++i)
	{
		const Real val = 0.5 * (1 - std::cos((2 * pi * i) / (N - 1)));
		res.emplace_back(val);
	}
	return res;
}
	
}