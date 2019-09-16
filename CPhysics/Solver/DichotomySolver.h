#pragma once

#include "OneDimensionalSolver.h"

namespace CPhysics
{

class DichotomySolver : public OneDimensionalSolver
{
public:
	DichotomySolver() = default;
	virtual ~DichotomySolver() = default;

	std::string		GetSolverType() const override;

	Real			Solve(const Params* params) const override;

};

}

