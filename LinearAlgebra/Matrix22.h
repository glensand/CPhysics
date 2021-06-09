/* Copyright (C) 2019 - 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/CPhysics
 */

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

inline double Matrix22::At(size_t i, size_t j) const
{
	return m_x[i * 2 + j];
}

inline double Matrix22::Deter() const
{
	return m_x[0] * m_x[3] - m_x[1] * m_x[2];
}

inline Matrix22 Matrix22::Inv() const
{
	const auto deter = Deter();
	if (deter == 0) return Matrix22{ };

	return { m_x[3] / deter, -m_x[2] / deter, -m_x[1] / deter, m_x[0] / deter };
}

inline Vector2 Matrix22::operator*(const Vector2 &vec) const
{
	return { m_x[0] * vec.At(0) + m_x[1] * vec.At(1), m_x[2] * vec.At(0) + m_x[3] * vec.At(1) };
}

