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

namespace CPhysics
{

using Real = double;

typedef Real(*OneDimensionalFunction)(Real x);

struct Params
{
	virtual ~Params() = default;
};

}
