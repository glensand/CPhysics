#include "TridiagonalSolver.h"


namespace CPhysics
{
//------------------------------------------------------------------------------
std::vector<Real> TridiagonalSolver::Solve(const Params* params) const
{
	if (!SuitableParams(params)) return std::vector<Real>{};
	const auto tParams = reinterpret_cast<const TridiagonalParams*>(params);
	
	std::vector<Real>
		d{ tParams->m_d },
		b{ tParams->m_b };

	const auto &a = tParams->m_a;
	const auto &c = tParams->m_c;

	std::vector<Real> w(b.size(), 0);
	for (size_t i = 1; i < b.size(); ++i)
	{
		const Real xi = a[i] / b[i - 1];
		b[i] -= xi * c[i - 1];
		d[i] -= xi * d[i - 1];
	}

	w.back() = d.back() / b.back();
	for (int64_t i = b.size() - 2; i >= 0; --i)
		w[i] = (d[i] - c[i] * w[i + 1]) / b[i];
	
	return w;
}
//------------------------------------------------------------------------------
bool TridiagonalSolver::SuitableParams(const Params* params) const
{
	const auto solverParams = dynamic_cast<const TridiagonalParams*>(params);
	return solverParams != nullptr;
}
//------------------------------------------------------------------------------
std::string TridiagonalSolver::GetSolverType() const
{
	return "Tridiagonal Solver ";
}
//------------------------------------------------------------------------------
}
	
