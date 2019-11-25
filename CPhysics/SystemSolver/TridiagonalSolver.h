#pragma once

#include "../CPhysics.h"
#include "ISystemSolver.h"

#include <vector>

namespace CPhysics {

struct TridiagonalParams final : Params
{
	std::vector<Real> m_a; // coefficients of three matrix diagonals
	std::vector<Real> m_b;
	std::vector<Real> m_c; 

	std::vector<Real> m_d; //right side


	TridiagonalParams(const std::vector<Real>& a, const std::vector<Real>& b, const std::vector<Real>& c,
		const std::vector<Real>& d)
		: m_a(a),
		  m_b(b),
		  m_c(c),
		  m_d(d)
	{
	}
};

class TridiagonalSolver final : public ISystemSolver
{
public:
			TridiagonalSolver() = default;
	virtual ~TridiagonalSolver() = default;
	
	std::vector<Real>			Solve(const Params* params) const override;

	bool						SuitableParams(const Params* params) const override;

	[[nodiscard]] std::string	GetSolverType() const override;
};

}