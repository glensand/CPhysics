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

	Real			Solve(SolverParams* params) const override;

};

}

