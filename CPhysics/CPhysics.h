//------------------------------------------------------------------------------
// CPhysics.h
// General library header file, consists of very basic structs and typedefs 
//
// Copyright (c) 2019 GlenSand
// All rights reserved.
//
// Date: 27.09.2019
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#pragma once

#include <vector>

namespace CPhysics
{

using Real = double;

typedef Real(*OneDimensionalFunction)(Real x);

//typedef Real(*FunctionOfXAndU)(Real x, OneDimensionalFunction u);

typedef Real(*FunctionOfTwoArgs)(Real x, Real y);

typedef Real(*FunctionOfVector)(std::vector<Real> args);
//==============================================================================	
struct Params
{
	virtual ~Params() = default;
};
//==============================================================================	
}
