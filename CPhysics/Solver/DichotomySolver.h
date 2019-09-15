#pragma once

#include "BaseSolver.h"

namespace CPhysics
{

class DichotomySolver : public BaseSolver
{
public:
	DichotomySolver() = default;
	virtual ~DichotomySolver() = default;

	std::string		GetSolverType() const override;

	Real			Solve(OneDimensionalFunction function, Real leftX, Real rightX) const override;

};

}

