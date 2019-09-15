#pragma once
#include <vector>
#include <string>

#include "Integrator/Intergator.h"

class Facade final
{
public:

	struct TestParams final
	{
		std::vector< CPhysics::IIntegrator*>	m_integrators;
	
		CPhysics::OneDimensionalFunction		m_function;
		const std::vector<size_t>				m_intervals;
		const std::string						m_functionString;
		
		const CPhysics::Real					m_analyticalValue;

		const CPhysics::Real					m_leftX;
		const CPhysics::Real					m_rightX;
	};
	
	Facade() = default;
	~Facade() = default;

	static void Test(const TestParams& params);
};
