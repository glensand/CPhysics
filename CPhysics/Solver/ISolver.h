#pragma once
#include <string>

#include "..//CPhysics.h"

namespace CPhysics
{

struct SolverParams : Params
{
	virtual ~SolverParams() = default;
	Real	m_accuracy{ };
};
	
class ISolver
{
public:
			ISolver() = default;
	virtual ~ISolver() = default;

	virtual std::string		GetSolverType() const = 0;

	virtual Real			Solve(const Params* params) const = 0;

	virtual bool			SuitableParams(const Params* params) const = 0;
};

}