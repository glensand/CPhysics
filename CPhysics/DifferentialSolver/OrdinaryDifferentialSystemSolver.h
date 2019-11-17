#pragma once
#include "IDifferentialSystemSolver.h"

namespace CPhysics
{
//==============================================================================	
struct OrdinaryDifferentialSystemParams : Params
{
	virtual ~OrdinaryDifferentialSystemParams() = default;
	
	size_t							m_knotAmount;
	Real							m_left_x;
	Real							m_right_x;
	Real							m_h;			// iteration step
	std::vector<FunctionOfVector>	m_functions;
	std::vector<Real>				m_conditions;	// values of unknowns on the left border, in order of equations	
};
using ODSParams = OrdinaryDifferentialSystemParams;
//==============================================================================	
class OrdinaryDifferentialSystemSolver : public IDifferentialSystemSolver
{
public:
	virtual ~OrdinaryDifferentialSystemSolver() = default;
	OrdinaryDifferentialSystemSolver() = default;

	bool SuitableParams(const Params* params) const override;
};
//==============================================================================	
}
