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
//==============================================================================	
//	all forward declarations should be placed here 
struct Point2D;
struct Point3D;
//==============================================================================	
using Real = double;

using Function1d = std::function<Real(Real)>;

using FunctionOfTwoArgs = std::function<Real(Real, Real)>;

using FunctionOfVector = std::function<Real(Real x, std::vector<Real>&)>;

//==============================================================================	
struct Params
{
	virtual ~Params() = default;
};
//==============================================================================
struct Point2D final
{
	Point2D(Real x, Real y)
		: m_x(x)
		, m_y(y){}
	~Point2D() = default;
	
	Real m_x;
	Real m_y;
};
//==============================================================================	
struct Point3D final
{
	Real m_x;
	Real m_y;
	Real m_z;
};
//==============================================================================	
}
