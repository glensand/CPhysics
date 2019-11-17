//------------------------------------------------------------------------------
// Vector2.h
// ...
//
// Copyright (c) 2019 GlenSand
// All rights reserved.
//
// Date: 17.11.2019
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#pragma once

class Vector2 final
{
public:
	Vector2(double x1, double x2)
		: m_x{ x1, x2 } {}
	~Vector2() = default;

	[[nodiscard]] double At(size_t i) const;
private:
	double	m_x[2];
};
//------------------------------------------------------------------------------
inline double Vector2::At(size_t i) const
{
	return m_x[i];
}
