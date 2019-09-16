#pragma once

#include "ISolver.h"

namespace CPhysics
{

struct OneDimensionalParams : public SolverParams
{
	Real					m_leftX{ };
	Real					m_rightX{ };
	OneDimensionalFunction	m_function{ };
};

class OneDimensionalSolver : public ISolver
{
public:
			OneDimensionalSolver() = default;
	virtual	~OneDimensionalSolver() = default;

	bool	SuitableParams(SolverParams* params) const override;

};

}
