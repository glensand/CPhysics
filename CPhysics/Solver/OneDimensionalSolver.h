#pragma once

#include "ISolver.h"

namespace CPhysics
{

struct OneDimensionalParams : Params
{
	Real					m_accuracy{ };
	Real					m_leftX{ };
	Real					m_rightX{ };
	OneDimensionalFunction	m_function{ };
};

class OneDimensionalSolver : public ISolver
{
public:
			OneDimensionalSolver() = default;
	virtual	~OneDimensionalSolver() = default;

	bool	SuitableParams(const Params* params) const override;

};

}
