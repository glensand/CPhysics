//------------------------------------------------------------------------------
// Kramer2Solver.h
// ...
//
// Copyright (c) 2019 GlenSand
// All rights reserved.
//
// Date: 17.11.2019
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#pragma once
#include "../CPhysics.h"
#include <tuple>
#include <Matrix22.h>
#include <Vector2.h>

namespace CPhysics
{
class Kramer2Solver final
{
	Kramer2Solver() = default;
	~Kramer2Solver() = default;

public:

	static std::tuple<Real, Real> Solve(const Matrix22& matrix, const Vector2& right);
};
//------------------------------------------------------------------------------
inline std::tuple<Real, Real> Kramer2Solver::Solve(const Matrix22& matrix, const Vector2& right)
{
	const auto deter = matrix.Deter();
	if (deter == 0) return { 0 , 0 };
	const Matrix22 mat1(right.At(0), matrix.At(0, 1), right.At(1), matrix.At(1,1));
	const Matrix22 mat2(matrix.At(0, 0), right.At(0), matrix.At(1,0), right.At(1));

	return { mat1.Deter() / deter, mat2.Deter() / deter };
}
//------------------------------------------------------------------------------	
}
