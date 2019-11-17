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

class Matrix22 final
{
public:
	Matrix22(double x11, double x12, double x21, double x22)
		: m_x{ x11, x12, x21, x22 } {}

	[[nodiscard]] double At(size_t i, size_t j) const;

	[[nodiscard]] double Deter() const;
private:
	double m_x[4];
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