/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/CPhysics
 */

#pragma once

#include "Vector3.h"
#include <utility>

class Matrix33 final
{
public:
    Matrix33(Vector3* vec);
	Matrix33() = default;
	~Matrix33() = default;
	
	[[nodiscard]] double	At(size_t i, size_t j) const;
	[[nodiscard]] Vector3&	operator[](size_t i);
	[[nodiscard]] const Vector3&	operator[](size_t i) const;
	[[nodiscard]] double	Det() const;
	[[nodiscard]] Matrix33	Inv() const;
	[[nodiscard]] Matrix33	Transpose() const;
	[[nodiscard]] Vector3	operator*(const Vector3& vec) const;
	[[nodiscard]] bool		operator==(const Matrix33& rhs) const;

private:
	Vector3 m_matrix[3];
};

inline
Matrix33::Matrix33(Vector3* vec)
    : m_matrix{vec[0], vec[1], vec[2]}
{

}

inline
double Matrix33::At(size_t i, size_t j) const
{
	return m_matrix[i][j];
}

inline
Vector3& Matrix33::operator[](size_t i)
{
	return m_matrix[i];
}

inline
const Vector3& Matrix33::operator[](size_t i) const
{
	return m_matrix[i];
}

inline
double Matrix33::Det() const
{
	return
		m_matrix[0][0] * m_matrix[1][1] * m_matrix[2][2] +
		m_matrix[0][1] * m_matrix[1][2] * m_matrix[2][0] +
		m_matrix[0][2] * m_matrix[1][0] * m_matrix[2][1] -
		m_matrix[0][2] * m_matrix[1][1] * m_matrix[2][0] -
		m_matrix[0][0] * m_matrix[1][2] * m_matrix[2][1] -
		m_matrix[0][1] * m_matrix[1][0] * m_matrix[2][2];
}

inline
Matrix33 Matrix33::Inv() const
{
	Matrix33 result;
	auto&& det = Det();

	auto&& row0 = result[0];
	row0[0] = (m_matrix[1][1] * m_matrix[1][1] - m_matrix[1][2] * m_matrix[2][1]) / det;
	row0[1] = (m_matrix[0][2] * m_matrix[2][1] - m_matrix[0][1] * m_matrix[2][2]) / det;
	row0[2] = (m_matrix[0][1] * m_matrix[1][2] - m_matrix[0][2] * m_matrix[1][1]) / det;

	auto&& row1 = result[1];
	row1[0] = (m_matrix[1][2] * m_matrix[2][0] - m_matrix[1][0] * m_matrix[2][2]) / det;
	row1[1] = (m_matrix[0][0] * m_matrix[2][2] - m_matrix[0][2] * m_matrix[2][0]) / det;
	row1[2] = (m_matrix[0][2] * m_matrix[1][0] - m_matrix[0][0] * m_matrix[1][2]) / det;

	auto&& row2 = result[2];
	row2[0] = (m_matrix[1][0] * m_matrix[2][1] - m_matrix[1][1] * m_matrix[2][0]) / det;
	row2[1] = (m_matrix[0][1] * m_matrix[2][0] - m_matrix[0][0] * m_matrix[2][1]) / det;
	row2[2] = (m_matrix[0][0] * m_matrix[1][1] - m_matrix[0][1] * m_matrix[1][0]) / det;

	return result;
}

inline
Matrix33 Matrix33::Transpose() const
{
	auto result = *this;
	std::swap(result[0][1], result[1][0]);
	std::swap(result[0][2], result[2][0]);
	std::swap(result[1][2], result[2][1]);
	return result;
}

inline
Vector3 Matrix33::operator*(const Vector3& vec) const
{
	Vector3 result(0.0, 0.0, 0.0);
	for (std::size_t i{ 0 }; i < 3; ++i)
		result[i] = m_matrix[i] * vec;
		
	return result;
}

inline
bool Matrix33::operator==(const Matrix33& rhs) const
{
	bool equal{ true };
    for(std::size_t i{ 0 }; i < 3; ++i)
    {
        if(!(m_matrix[i] == rhs[i]))
        {
			equal = false;
			break;
        }
    }
	return equal;
}
