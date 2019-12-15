#include "SpectralProblemSolver.h"

#include "../SystemSolver/TridiagonalSolver.h"

namespace
{
//------------------------------------------------------------------------------	
void  diff(std::vector<CPhysics::Real> &x0, const std::vector<CPhysics::Real> &x1)
{
	if(x0.size() != x1.size()) return;

	for(size_t i{ 0 }; i < x0.size(); ++i) 
		x0[i] -= x1[i];
}
//------------------------------------------------------------------------------	
CPhysics::Real  inner(const std::vector<CPhysics::Real>& x0, const std::vector<CPhysics::Real>& x1)
{
	if (x0.size() != x1.size()) return CPhysics::Real(0.0);

	CPhysics::Real result{ 0.0 };
	
	for (size_t i{ 0 }; i < x0.size(); ++i)
		result += x0[i] * x1[i];
}
//------------------------------------------------------------------------------	
CPhysics::Real norm(const std::vector <CPhysics::Real> &x)
{
	CPhysics::Real length2{ 0.0 };

	for (size_t i{ 0 }; i < x.size(); ++i)
		length2 += x[i] * x[i];

	return std::sqrt(length2);
}
//------------------------------------------------------------------------------	
std::vector<CPhysics::Real> mult(const std::vector<CPhysics::Real> &x, CPhysics::Real c)
{
	std::vector<CPhysics::Real> res;
	res.reserve(x.size());
	
	for(size_t i{ 0 }; i < x.size(); ++i) res.emplace_back(x[i] * c);

	return res;
}
//------------------------------------------------------------------------------	
}

namespace  CPhysics
{
//------------------------------------------------------------------------------	
IDifferentialSystemSolver::ReturnType SpectralProblemSolver::Solve(const Params* params) const
{
	ReturnType result;
	if (!SuitableParams(params)) return result;

	const auto spectralParams = reinterpret_cast<const SpectralProblemSolverParams*>(params);
	const TridiagonalSolver solver;
	
	result.reserve(spectralParams->m_m);
	result.emplace_back(std::vector<Real>());

	const auto ride = [&](size_t i, std::vector<Real> &d2, const std::vector<Real> &y)
	{
		for (size_t k{ 0 }; k < i; k++)
		{
			const Real innerPsi = inner(y, result[k + 1]);
			const Real normPsi = norm(result[k + 1]);
			diff(d2, mult(result[k + 1], innerPsi / normPsi));
		}
	};
	
	for(size_t i{ 0 }; i < spectralParams->m_m; ++i )
	{
		auto d2 = spectralParams->m_y0;

		ride(i, d2, spectralParams->m_y0);
		Real normD2{ };
		for(size_t j{ 0 }; j < spectralParams->m_N; ++j)
		{
			normD2 = norm(d2);
			const TridiagonalParams triParams(spectralParams->m_a, spectralParams->m_b,
				spectralParams->m_c, d2);

			d2 = solver.Solve(&triParams);

			ride(i, d2, d2);
		}

		const auto E0 = normD2 / norm(d2);
		result[0].emplace_back(E0);
		//result.emplace_back(d2);
		result.emplace_back(mult(d2, 1 / norm(d2)));
	}
	return result;
}
//------------------------------------------------------------------------------
std::string SpectralProblemSolver::GetSolverType() const
{
	return "Spectral problem solver";
}
//------------------------------------------------------------------------------
bool SpectralProblemSolver::SuitableParams(const Params* params) const
{
	return dynamic_cast<const SpectralProblemSolverParams*>(params) != nullptr;
}
//------------------------------------------------------------------------------
}
