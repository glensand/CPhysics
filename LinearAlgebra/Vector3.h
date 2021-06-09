/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/CPhysics
 */

#pragma once

#include <cmath>

class Vector3 final
{
public:
    Vector3(double x1, double x2, double x3);
	~Vector3() = default;

	[[nodiscard]] double At(size_t i) const { return m_x[i]; }
	[[nodiscard]] double operator[](size_t i) const { return m_x[i]; }
	[[nodiscard]] double& operator[](size_t i) { return m_x[i]; }
    [[nodiscard]] double Norm() const;
	void Normalize();
	friend Vector3 Cross(const Vector3& left, const Vector3& right);
	friend double Dot(const Vector3& left, const Vector3& right);

private:
	double	m_x[3];
};

inline
Vector3 Cross(const Vector3& left, const Vector3& right)
{
	return Vector3(left[1] * right[2] - left[2] * right[1], left[2] * right[0] - left[0] * right[2], left[0] * right[1] - left[1] * right[0]);
}

inline
double Dot(const Vector3& left, const Vector3& right)
{
	return left[0] * right[0] + left[1] * right[1] + left[2] * right[2];
}

inline
Vector3::Vector3(double x1, double x2, double x3)
    : m_x{x1, x2, x3}
{
}

inline
double Vector3::Norm() const
{
    return std::sqrt(m_x[0] * m_x[0] + m_x[1] * m_x[1] + m_x[2] * m_x[2]);
}

inline
void Vector3::Normalize()
{
	double norma = Norm();
	for (auto& x : m_x)
		x /= norma;
}
