#include  <iostream>

template<typename T>
T ComputePrecigion(T eps)
{
	size_t i = 0;
	for (i = 0; eps / 2 + 1 != 1; ++i)
		eps = eps / 2;

	std::cout << "d: " << i << std::endl;
	return eps;
}
//--------------------------------------------------------------
template<typename T>
int computeMaxExp(T eps)
{
	size_t i = 0;
	for (; eps < eps * 2; ++i)
		eps = eps * 2;

	return i;
}
//--------------------------------------------------------------
template<typename T>
int computeMinExp(T eps)
{
	size_t i = 0;
	for (; eps/ 2 != 0; ++i)
		eps = eps / 2;

	return i;
}
//--------------------------------------------------------------
int main()
{
	float eps1 = 1;

	std::cout << "float: " << std::endl;
	std::cout << "eps: " << ComputePrecigion(eps1) << std::endl;
	std::cout << "min exp: " << computeMinExp(eps1) << std::endl;
	std::cout << "max exp: " << computeMaxExp(eps1) << std::endl;
	
	double eps2 = 1;
	std::cout << "Real: " << std::endl;
	std::cout << "eps, Real: " << ComputePrecigion(eps2) << std::endl;
	std::cout << "min exp: " << computeMinExp(eps2) << std::endl;
	std::cout << "max exp: " << computeMaxExp(eps2) << std::endl;

	auto eps = ComputePrecigion(eps2);
	std::cout << "1 < 1 + eps: " << (1 < eps) << std::endl;
	std::cout << "1 + eps > 1 + eps / 2: " << (1 + eps > 1 + eps / 2) << std::endl;
	std::cout << "1  + eps < 1 + eps + eps / 2: " << (1 + eps < 1 + eps + eps / 2) << std::endl;
	std::cout << "1  + eps  + eps / 2 > 1 + eps / 2 + eps: " << (1 + eps + eps / 2 > 1 + eps / 2 + eps) << std::endl;

	return 0;
}