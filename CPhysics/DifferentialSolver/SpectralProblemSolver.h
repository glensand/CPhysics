//------------------------------------------------------------------------------
// SpectralProblemSolver.h
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

namespace CPhysics
{
//==============================================================================
struct SpectralProblemSolverParams : Params
{
	// magic params
	std::vector<Real>	m_y0;
	std::vector<Real>	m_a;
	std::vector<Real>	m_b;
	std::vector<Real>	m_c;
	size_t				m_N;
	size_t				m_m;

	SpectralProblemSolverParams(const std::vector<Real>& y0, const std::vector<Real>& a,
		const std::vector<Real>& b, const std::vector<Real>& c, size_t N, size_t m)
		: m_y0(y0),
		  m_a(a),
		  m_b(b),
		  m_c(c),
		  m_N(N),
		  m_m(m)
	{}
};
//==============================================================================	
class SpectralProblemSolver : public OrdinaryDifferentialSystemSolver
{
public:

	SpectralProblemSolver() = default;
	virtual ~SpectralProblemSolver() = default;

	ReturnType					Solve(const Params* params) const override;

	[[nodiscard]] std::string	GetSolverType() const override;

	bool						SuitableParams(const Params* params) const override;
};
}


