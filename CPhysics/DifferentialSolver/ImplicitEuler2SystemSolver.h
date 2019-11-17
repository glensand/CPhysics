//------------------------------------------------------------------------------
// ImplicitEuler2SystemSolver.h
// ...
//
// Copyright (c) 2019 GlenSand
// All rights reserved.
//
// Date: 17.11.2019
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#pragma once

#include "OrdinaryDifferentialSystemSolver.h"
#include "../../LinearAlgebra/Matrix22.h"

namespace CPhysics
{
//==============================================================================
struct ImplicitEuler2SystemSolverParams : Params
{
	virtual ~ImplicitEuler2SystemSolverParams() = default;
	ImplicitEuler2SystemSolverParams(const Matrix22& mat22, Real v0, Real u0, size_t kAmount)
	: m_m22(mat22)
	, m_u0(u0)
	, m_v0(v0)
	, m_knotAmount(kAmount)
	{}

	Matrix22	m_m22;
	Real		m_u0;
	Real		m_v0;
	size_t		m_knotAmount;
};
//==============================================================================	
class ImplicitEuler2SystemSolver : public OrdinaryDifferentialSystemSolver
{
public:
	virtual ~ImplicitEuler2SystemSolver() = default;
	ImplicitEuler2SystemSolver() = default;

	[[nodiscard]] std::string	GetSolverType() const override;

	ReturnType					Solve(const Params* params) const override;

	bool						SuitableParams(const Params* params) const override;
};
//==============================================================================	
}

