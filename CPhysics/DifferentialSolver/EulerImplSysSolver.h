#pragma once

#include "OrdinaryDifferentialSystemSolver.h"
#include "../CPhysics.h"

namespace CPhysics
{

class EulerImplSysSolver final : public IDifferentialSystemSolver
{
public:
	EulerImplSysSolver() = default;
	~EulerImplSysSolver() = default;

	ReturnType Solve(const Params* params) const override;
};
	
}