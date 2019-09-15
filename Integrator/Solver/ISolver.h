#pragma once
#include <string>

#include "..//CPhysics.h"
#include <vector>

namespace CPhysics
{

class ISolver
{
public:
			ISolver() = default;
	virtual ~ISolver() = default;

	virtual std::string GetSolverType() const = 0;

	virtual Real Solve(OneDimensionalFunction function, Real x0) const = 0;
};

}