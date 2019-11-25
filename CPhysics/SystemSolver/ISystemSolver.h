#pragma once

#include "../CPhysics.h"

#include <vector>

namespace CPhysics
{

class ISystemSolver
{
public:
	ISystemSolver() = default;
	virtual ~ISystemSolver() = default;

	virtual std::vector<Real>			Solve(const Params* params) const = 0;

	virtual bool						SuitableParams(const Params* params) const = 0;

	[[nodiscard]] virtual std::string	GetSolverType() const = 0;
};

}