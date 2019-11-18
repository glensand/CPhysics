#pragma once

#include "../CPhysics.h"

#include <vector>

namespace CPhysics {


class ISystemSolver
{
public:
	ISystemSolver() = default;
	virtual ~ISystemSolver() = default;

	virtual std::vector<Real> Solve(Params* params) = 0;

	virtual bool SuitableParams(Params* params) = 0;

	virtual std::string GetSolverType() = 0;
};

}