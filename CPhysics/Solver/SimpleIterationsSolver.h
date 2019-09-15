#pragma once

#include "BaseSolver.h"

namespace CPhysics
{

class SimpleIterationsSolver : public BaseSolver
{
public:
	SimpleIterationsSolver() = default;
	virtual ~SimpleIterationsSolver() = default;

	std::string		GetSolverType() const override;

	Real			Solve(OneDimensionalFunction function, Real leftX, Real rightX) const override;

};

}

