#include  <iostream>

template<typename T>
T ComputePrecision(T eps)
{
	size_t i{ 0 };
	for (; eps / 2 + 1 != 1; ++i)
		eps = eps / 2;

	std::cout << "d: " << i << std::endl;
	return eps;
}
//--------------------------------------------------------------
template<typename T>
size_t ComputeMaxExp(T eps)
{
	size_t i{ 0 };
	for (; eps < eps * 2; ++i)
		eps = eps * 2;

	return i;
}
//--------------------------------------------------------------
template<typename T>
size_t ComputeMinExp(T eps)
{
	size_t i{ 0 };
	for (; eps/ 2 != 0; ++i)
		eps = eps / 2;

	return i;
}
//--------------------------------------------------------------
int main()
{
	constexpr float eps1 = 1;

	std::cout << "float: " << std::endl;
	std::cout << "eps: " << ComputePrecision(eps1) << std::endl;
	std::cout << "min exp: " << ComputeMinExp(eps1) << std::endl;
	std::cout << "max exp: " << ComputeMaxExp(eps1) << std::endl;
	
	constexpr double eps2 = 1;
	std::cout << "Real: " << std::endl;
	std::cout << "eps, Real: " << ComputePrecision(eps2) << std::endl;
	std::cout << "min exp: " << ComputeMinExp(eps2) << std::endl;
	std::cout << "max exp: " << ComputeMaxExp(eps2) << std::endl;

	const auto eps = ComputePrecision(eps2);
	std::cout << "1 < 1 + eps: " << (1 < eps) << std::endl;
	std::cout << "1 + eps > 1 + eps / 2: " << (1 + eps > 1 + eps / 2) << std::endl;
	std::cout << "1  + eps < 1 + eps + eps / 2: " << (1 + eps < 1 + eps + eps / 2) << std::endl;
	std::cout << "1  + eps  + eps / 2 > 1 + eps / 2 + eps: " << (1 + eps + eps / 2 > 1 + eps / 2 + eps) << std::endl;

	return 0;
}