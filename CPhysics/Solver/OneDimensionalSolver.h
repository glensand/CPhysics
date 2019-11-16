#pragma once
//------------------------------------------------------------------------------
// OneDimensionalSolver.h
// Base class for equation solvers with one argument
//
// Copyright (c) 2019 GlenSand
// All rights reserved.
//
// Date: 27.09.2019
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#include "ISolver.h"

namespace CPhysics
{
//==============================================================================
struct ByStepD1Result : ByStepResult
{
	virtual ~ByStepD1Result() = default;

	std::vector<Real>	m_xs{ };
	std::vector<Real>	m_ys{ };

	Real				m_res{ };
};
//==============================================================================
struct OneDimensionalSolverParams : Params
{
	OneDimensionalSolverParams(Real accuracy, Real left, Real right, const Function1d &func)
		: m_accuracy(accuracy)
		, m_leftX(left)
		, m_rightX(right)
		, m_function(func)
	{}
	Real					m_accuracy{ };
	Real					m_leftX{ };
	Real					m_rightX{ };
	Function1d				m_function{ };
};
//==============================================================================
class OneDimensionalSolver : public ISolver
{
public:
			OneDimensionalSolver() = default;
	virtual	~OneDimensionalSolver() = default;

	bool	SuitableParams(const Params* params) const override;

};
//==============================================================================
}
