//метод прогонки
#pragma once

#include "ISolver.h"
#include "../CPhysics.h"

#include <vector>

namespace CPhysics {


	
struct TridiagonalParams final : Params
{
	std::vector<Real> a, b, c; // coefficients of three matrix diagonals
	std::vector<Real> d; //right side
};

//TODO make an interface for solver

class TridiagonalSolver final
{
public:
	TridiagonalSolver() = default;
	~TridiagonalSolver() = default;
	
	std::vector<Real> Solve(Params* params);
	static bool SuitableParams(Params* params);
	std::string GetSolverType()
	{
		return "Tridiagonal Solver (метод прогонки)";
	}
};

}