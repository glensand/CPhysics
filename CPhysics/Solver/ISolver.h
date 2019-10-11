#pragma once
//------------------------------------------------------------------------------
// ISolver.h
// General equation solver interface
//
// Copyright (c) 2019 GlenSand
// All rights reserved.
//
// Date: 27.09.2019
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#include <string>

#include "..//CPhysics.h"

namespace CPhysics
{
//==============================================================================	
struct SolverParams : Params
{
	virtual ~SolverParams() = default;
	Real	m_accuracy{ };
};
//==============================================================================	
class ISolver
{
public:
			ISolver() = default;
	virtual ~ISolver() = default;

	virtual std::string		GetSolverType() const = 0;

	virtual Real			Solve(const Params* params) const = 0;

	virtual bool			SuitableParams(const Params* params) const = 0;
};
//==============================================================================	
}