//------------------------------------------------------------------------------
// Euler2Solver.h
// Class for solving ordinary differential equations numerically through
// Euler's method of second accuracy order
//
// Copyright (c) 2019 Varumithu
// All rights reserved.
//
// Date: 10.10.2019
// Author: Bachurin Vladimir
//------------------------------------------------------------------------------
#pragma once

#include "SimpleDifferentialSolver.h"

namespace CPhysics
{
//==============================================================================
struct Euler2Params : Params
{
	Euler2Params(const Real left_x, const Real right_x, const Real left_cond, 
		const size_t knot_amount, const FunctionOfTwoArgs f, 
		const FunctionOfTwoArgs f_by_x, const FunctionOfTwoArgs f_by_u) :
		m_leftX(left_x), m_rightX(right_x), m_leftCond(left_cond),
		m_knotAmount(knot_amount), m_function(f), m_functionByX(f_by_x), m_functionByU(f_by_u)
	{}
	Euler2Params() = default;
	Real					m_leftX{ };
	Real					m_rightX{ };
	Real					m_leftCond{ };		// U(m_leftX) where U is the solution of the differential equation 
	size_t					m_knotAmount{ };
	FunctionOfTwoArgs		m_function{ };		// the right half of standard simple differential equation dU/dX = f(x, U(x))
	FunctionOfTwoArgs		m_functionByX{ };	// partial derivative of function by x
	FunctionOfTwoArgs		m_functionByU{ };	// partial derivative of function by u
};
//==============================================================================	
class Euler2Solver final : public ISimpleDifferentialSolver
{
public:
	Euler2Solver() = default;
	virtual	~Euler2Solver() = default;

	[[nodiscard]] std::string		GetSolverType() const override;

	bool	SuitableParams(const Params * params) const override;

	std::vector<Point2D> Solve(const Params* params) const override;
};
//==============================================================================
}
