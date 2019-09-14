#include "Facade.h"
#include <iostream>
 
void Facade::Test(const TestParams& params)
{
	const auto& function = params.m_function;
	const auto& leftX = params.m_leftX;
	const auto& rightX = params.m_rightX;

	std::cout << "//========================================================//" << std::endl;
	std::cout << "Test function: " << params.m_functionString << std::endl;
	std::cout << "integrate from: " << std::to_string(leftX) << " to: " << std::to_string(rightX) << std::endl;
	std::cout << "Analytical value: " << params.m_analyticalValue << std::endl;
	
	for(auto i : params.m_intervals)
	{
		if(i == 0)
			continue;

		std::cout << "//----------------------------------------------" << std::endl;
		std::cout << "count of intervals: " << std::to_string(i) << std::endl;

		for(const auto& integrator : params.m_integrators)
		{
			if(!integrator->SuitableParams(leftX, rightX, i))
				continue;
			
			const auto result = integrator->Integrate(function, leftX, rightX, i);
			std::cout << integrator->GetIntegratorType() << ": " << result;
			std::cout << "; difference with analytical value: " << result - params.m_analyticalValue << std::endl;
		}
	}
}
