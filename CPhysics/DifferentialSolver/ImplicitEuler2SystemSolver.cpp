#include "ImplicitEuler2SystemSolver.h"
#include "../Solver/Kramer2Solver.h"

namespace CPhysics
{
//------------------------------------------------------------------------------
std::string ImplicitEuler2SystemSolver::GetSolverType() const
{
	return "Solver for ordinary system of differential equations via implicit Eulers solver";
}
//------------------------------------------------------------------------------
IDifferentialSystemSolver::ReturnType ImplicitEuler2SystemSolver::Solve(const Params* params) const
{
	if (!SuitableParams(params)) return ReturnType{};

	const auto iDParams = dynamic_cast<const ImplicitEuler2SystemSolverParams*>(params);
	const auto& mat22 = iDParams->m_m22;
	
	std::vector<Real> uXes;
	std::vector<Real> vXes;

	uXes.reserve(iDParams->m_knotAmount);
	vXes.reserve(iDParams->m_knotAmount);

	uXes.emplace_back(iDParams->m_u0);
	vXes.emplace_back(iDParams->m_v0);

	for(size_t i{ 1 }; i < iDParams->m_knotAmount; ++i)
	{
		const auto [un1, vn1] = Kramer2Solver::Solve(mat22, { uXes[i - 1], vXes[i - 1] });
		uXes.emplace_back(un1);
		vXes.emplace_back(vn1);
	}

	return { uXes, vXes };
}
//------------------------------------------------------------------------------	
bool ImplicitEuler2SystemSolver::SuitableParams(const Params* params) const
{
	const auto p = dynamic_cast<const ImplicitEuler2SystemSolverParams*>(params);
	return p != nullptr;
}
//------------------------------------------------------------------------------	
}
