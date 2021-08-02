#include "OneDimensionalIntegratorFacade.h"
#include <iostream>
#include <Integrator/OneDimensional/OneDimensionalIntegrator.h>

void OneDimensionalIntegratorFacade::Test(const CPhysics::Params* params)
{
	const auto oneDimensionalIntegratorTestParams = dynamic_cast<const OneDimensionalIntegratorTestParams*>(params);
	if (params == nullptr) return;

	const auto& leftX = oneDimensionalIntegratorTestParams->m_leftX;
	const auto& rightX = oneDimensionalIntegratorTestParams->m_rightX;

	std::cout << "//========================================================//" << std::endl;
	std::cout << "Test function: " << oneDimensionalIntegratorTestParams->m_functionString << std::endl;
	std::cout << "integrate from: " << std::to_string(leftX) << " to: " << std::to_string(rightX) << std::endl;
	std::cout << "Analytical value: " << oneDimensionalIntegratorTestParams->m_analyticalValue << std::endl;
	
	for(auto i : oneDimensionalIntegratorTestParams->m_intervalsVector)
	{
		if(i == 0)
			continue;

		std::cout << "//----------------------------------------------" << std::endl;
		std::cout << "count of intervals: " << std::to_string(i) << std::endl;
		const CPhysics::Integrator1dParamsIntervals oneDimensionalIntegratorParams
		(leftX, rightX, oneDimensionalIntegratorTestParams->m_function, i);
		
		for(const auto& integrator : oneDimensionalIntegratorTestParams->m_integrators)
		{	
			const auto result = integrator->Integrate(&oneDimensionalIntegratorParams);
			std::cout << integrator->GetIntegratorType() << ": " << result;
			std::cout << "; difference with analytical value: " << result - oneDimensionalIntegratorTestParams->m_analyticalValue << std::endl;
		}
	}
}
