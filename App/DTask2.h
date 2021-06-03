#pragma once
#include "ITask.h"

#include "DifferentialSolver/CrankNicolsonDiffuseSolver.h"

class DTask2 : public ITask
{
public:
	virtual ~DTask2() = default;
	DTask2() = default;

	void Run(const Params* params = nullptr) override;
};
//------------------------------------------------------------------------------
inline void DTask2::Run(const Params* params)
{
	
}

