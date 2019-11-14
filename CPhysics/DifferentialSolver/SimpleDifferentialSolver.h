//------------------------------------------------------------------------------
// SimpleDifferentialSolver.h
// Interface for numerical solvers of single ordinary differential equation
// as well as params class
//
// Copyright (c) 2019 Varumithu
// All rights reserved.
//
// Date: 10.10.2019
// Author: Bachurin Vladimir
//------------------------------------------------------------------------------
#pragma once

#include "../Solver/ISolver.h"
#include  <vector>

namespace CPhysics
{
//==============================================================================
struct SimpleDifferentialParams : Params
{
	SimpleDifferentialParams(const Real left_x, const Real right_x, const Real left_cond,
		const size_t knot_amount, const FunctionOfTwoArgs f) :
			m_knotAmount(knot_amount), m_leftX(left_x), m_rightX(right_x),
			m_leftCond(left_cond), m_function(f)
	{}
	SimpleDifferentialParams() = default;
	size_t					m_knotAmount{ };
	Real					m_leftX{ };
	Real					m_rightX{ };
	Real					m_leftCond{ }; // U(m_leftX) where U is the solution of the differential equation 
	FunctionOfTwoArgs		m_function{ }; // the right half of standard simple differential equation dU/dX = f(x, U(x))
};
//==============================================================================
class ISimpleDifferentialSolver
{
public:
	ISimpleDifferentialSolver() = default;
	virtual	~ISimpleDifferentialSolver() = default;

	virtual bool		SuitableParams(const Params * params) const;

	virtual std::string	GetSolverType() const = 0;

	virtual std::vector<Point2D> Solve(const Params* params) const = 0;
};
//==============================================================================	
}