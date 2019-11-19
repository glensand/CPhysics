#pragma once

#include "IDifferentialSystemSolver.h"

namespace CPhysics
{
//==============================================================================
struct CrankNicolsonDiffuseSolverParams final : Params
{
	virtual ~CrankNicolsonDiffuseSolverParams() = default;
			CrankNicolsonDiffuseSolverParams() = default;
	
			CrankNicolsonDiffuseSolverParams(const Function1d &f, Real lx, Real rx, Real s, Real h, Real t)
				: m_func(f)
				, m_leftX(lx)
				, m_rightX(rx)
				, m_s(s)
				, m_h(h)
				, m_t(t)
				{}

	Function1d	m_func;

	Real		m_leftX;
	Real		m_rightX;

				// some related params, should be commented letter
	Real		m_s;
	Real		m_h;
	Real		m_t;
};
//==============================================================================
class CrankNicolsonDiffuseSolver : public IDifferentialSystemSolver
{
public:
	virtual ~CrankNicolsonDiffuseSolver() = default;
			CrankNicolsonDiffuseSolver() = default;

	[[nodiscard]] ReturnType	Solve(const Params* params) const override;

	[[nodiscard]] bool			SuitableParams(const Params* params) const override;

	[[nodiscard]] std::string	GetSolverType() const override;
};
//==============================================================================
}
