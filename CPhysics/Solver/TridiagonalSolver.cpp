#include "TridiagonalSolver.h"


namespace CPhysics
{

std::vector<CPhysics::Real> TridiagonalSolver::Solve(Params* params)
{
	auto TParams = reinterpret_cast<TridiagonalParams*>(params);
	
	std::vector<CPhysics::Real> x(TParams->b.size(), 0), a{TParams->a}, b{TParams->b},
								c{TParams->c}, d{TParams->d};
	c.push_back(0);
	a.insert(a.begin(), 0);
	std::vector<Real> w(b.size(), 0);
	for (size_t i = 1; i < b.size(); ++i)
	{
		w[i] = a[i] / b[i - 1];
		b[i] = b[i] - w[i] * c[i - 1];
		d[i] = d[i] - w[i] * d[i - 1];
		a[i] = 0;
	}

	x[b.size() - 1] = d[b.size() - 1] / b[b.size() - 1];
	for (long int i = b.size() - 2; i >= 0; --i)
	{
		x[i] = (d[i] - c[i] * x[i + 1]) / b[i];
	}
	
	return x;
	
}

bool TridiagonalSolver::SuitableParams(Params* params)
{
	const auto solverParams = dynamic_cast<const TridiagonalParams*>(params);
	if (solverParams)
		if ((solverParams->b.size() == solverParams->d.size()) || 
			(solverParams->c.size() == solverParams->a.size()) || 
			(solverParams->a.size() == solverParams->b.size() - 1)) 
		{
			return true;
		}

	return false;
}
	
}
	
