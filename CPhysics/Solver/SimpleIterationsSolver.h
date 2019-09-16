#pragma once

#include "OneDimensionalSolver.h"

namespace CPhysics
{

class SimpleIterationsSolver : public OneDimensionalSolver
{
public:
	SimpleIterationsSolver() = default;
	virtual ~SimpleIterationsSolver() = default;

	std::string		GetSolverType() const override;

	Real			Solve(const Params* params) const override;

};

}

