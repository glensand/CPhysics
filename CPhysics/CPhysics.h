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
#include <functional>

namespace CPhysics
{

using Real = double;

using Function1d = std::function<Real(Real)>;

//typedef Real(*Function1d)(Real x);
//typedef Real(*FunctionOfXAndU)(Real x, Function1d u);

typedef Real(*FunctionOfTwoArgs)(Real x, Real y);

typedef Real(*FunctionOfVector)(std::vector<Real> args);
//==============================================================================	
struct Params
{
	virtual ~Params() = default;
};
//==============================================================================	
}
