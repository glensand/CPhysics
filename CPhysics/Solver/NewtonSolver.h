#pragma once

#include "BaseSolver.h"

namespace CPhysics
{

class NewtonSolver : public BaseSolver
{
public:
	NewtonSolver() = default;
	virtual ~NewtonSolver() = default;

	std::string		GetSolverType() const override;

	Real			Solve(OneDimensionalFunction function, Real leftX, Real rightX) const override;

};

}

