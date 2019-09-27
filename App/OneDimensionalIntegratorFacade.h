#pragma once
#include <vector>
#include <string>

#include <Integrator/OneDimensionalIntegrator.h>

struct OneDimensionalIntegratorTestParams : CPhysics::OneDimensionalIntegratorParams
{
	OneDimensionalIntegratorTestParams(const std::vector< CPhysics::IIntegrator*> &integrators, const std::vector<size_t> &intervals,
	const std::string &stringFunction, CPhysics::Real analyticalValue, CPhysics::Real leftX, CPhysics::Real rightX, 
	CPhysics::OneDimensionalFunction function)
	:
	OneDimensionalIntegratorParams(leftX, rightX, function),
	m_integrators(integrators),
	m_intervalsVector(intervals),
	m_functionString(stringFunction),
	m_analyticalValue(analyticalValue)
	{}
	
	virtual ~OneDimensionalIntegratorTestParams() = default;

	std::vector< CPhysics::IIntegrator*>	m_integrators;

	const std::vector<size_t>				m_intervalsVector;
	const std::string						m_functionString;

	const CPhysics::Real					m_analyticalValue{ };
};

class OneDimensionalIntegratorFacade final
{
public:
	
	OneDimensionalIntegratorFacade() = default;
	~OneDimensionalIntegratorFacade() = default;

	static void Test(const CPhysics::Params* params);
};
