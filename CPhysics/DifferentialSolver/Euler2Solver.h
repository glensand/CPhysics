//------------------------------------------------------------------------------
// OneDimensionalSolver.h
// Base class for equation solvers with one argument
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


struct Euler2Params : Params
{
	Real					m_leftX{ };
	Real					m_rightX{ };
	Real					m_leftCond{ }; // U(m_leftX) where U is the solution of the differential equation 
	size_t					m_knotAmount{ };
	FunctionOfTwoArgs		m_function{ }; // the right half of standard simple differential equation dU/dX = f(x, U(x))
	FunctionOfTwoArgs		m_functionByX{ }; // partial derivative of function by x
	FunctionOfTwoArgs		m_functionByU{ }; // partial derivative of function by u 
};





	
class Euler2Solver final : public ISimpleDifferentialSolver
{
public:
	Euler2Solver() = default;
	virtual	~Euler2Solver() = default;

	std::string		GetSolverType() const override;
	bool	SuitableParams(const Params * params) const override;
	virtual std::vector<std::pair<Real, Real>> Solve(const Params* params) const override;
};



}
