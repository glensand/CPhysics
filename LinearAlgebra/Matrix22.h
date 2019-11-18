//------------------------------------------------------------------------------
// Matrix22.h
// ...
//
// Copyright (c) 2019 GlenSand
// All rights reserved.
//
// Date: 17.11.2019
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#pragma once
#include "Vector2.h"

class Matrix22 final
{
public:
	Matrix22(double x11, double x12, double x21, double x22)
		: m_x{ x11, x12, x21, x22 } {}

	Matrix22() = default;

	~Matrix22() = default;
	
	[[nodiscard]] double	At(size_t i, size_t j) const;

	[[nodiscard]] double	Deter() const;

	[[nodiscard]] Matrix22	Inv() const;

	[[nodiscard]] Vector2	operator*(const Vector2 &vec) const;
private:
	double m_x[4]{ };
};
//------------------------------------------------------------------------------
inline double Matrix22::At(size_t i, size_t j) const
{
	return m_x[i * 2 + j];
}
//------------------------------------------------------------------------------
inline double Matrix22::Deter() const
{
	return m_x[0] * m_x[3] - m_x[1] * m_x[2];
}
//------------------------------------------------------------------------------
inline Matrix22 Matrix22::Inv() const
{
	const auto deter = Deter();
	if (deter == 0) return Matrix22{ };

	return { m_x[3] / deter, -m_x[2] / deter, -m_x[1] / deter, m_x[0] / deter };
}
//------------------------------------------------------------------------------
inline Vector2 Matrix22::operator*(const Vector2 &vec) const
{
	return { m_x[0] * vec.At(0) + m_x[1] * vec.At(1), m_x[2] * vec.At(0) + m_x[3] * vec.At(1) };
}
//------------------------------------------------------------------------------
