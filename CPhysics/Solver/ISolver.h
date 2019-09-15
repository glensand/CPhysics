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

	virtual std::string		GetSolverType() const = 0;

	virtual Real			Solve(OneDimensionalFunction function, Real leftX, Real rightX) const = 0;

	virtual bool			SuitableParams(Real leftX, Real rightX) const = 0;
};

}