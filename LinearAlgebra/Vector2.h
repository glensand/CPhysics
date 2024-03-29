/* Copyright (C) 2019 - 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/CPhysics
 */

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

inline double Vector2::At(size_t i) const
{
	return m_x[i];
}
