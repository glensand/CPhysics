#pragma once

#include "../CPhysics.h"
#include "ISystemSolver.h"

#include <vector>

namespace CPhysics {

struct TridiagonalParams final : Params
{
	std::vector<Real> a, b, c; // coefficients of three matrix diagonals
	std::vector<Real> d; //right side
};


class TridiagonalSolver final : public ISystemSolver
{
public:
	TridiagonalSolver() = default;
	~TridiagonalSolver() = default;
	
	std::vector<Real> Solve(Params* params) override;

	bool SuitableParams(Params* params) override;

	std::string GetSolverType() override;
};

}