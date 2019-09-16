#pragma once

#include "OneDimensionalSolver.h"

namespace CPhysics
{

class NewtonSolver : public OneDimensionalSolver
{
public:
	NewtonSolver() = default;
	virtual ~NewtonSolver() = default;

	std::string		GetSolverType() const override;

	Real			Solve(SolverParams* params) const override;

};

}

