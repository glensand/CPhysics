/* Copyright (C) 2019 - 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/CPhysics
 */

#pragma once
#include "Vector3.h"

class Matrix33 final
{
public:
	Matrix33(Vector3* vec)
		: m_matrix{ vec[0], vec[1], vec[2] } {}

	~Matrix33() = default;
	
	[[nodiscard]] double	At(size_t i, size_t j) const;
	[[nodiscard]] Vector3&	operator[](size_t i);
	[[nodiscard]] const Vector3&	operator[](size_t i) const;
	[[nodiscard]] double	Det() const;
	[[nodiscard]] Matrix33	Inv() const;
	[[nodiscard]] Matrix33	Transpose() const;
	[[nodiscard]] Vector3	operator*(const Vector3& vec) const;

private:
	Vector3 m_matrix[3];
};

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
}

inline
Matrix33 Matrix33::Inv() const
{
}

inline
Matrix33 Matrix33::Transpose() const
{
}

inline
Vector3 Matrix33::operator*(const Vector3& vec) const
{

}
