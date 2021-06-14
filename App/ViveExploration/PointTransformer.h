/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/CPhysics
 */

#pragma once

#include "Matrix33.h"

class PointTransformer final
{
public:
    PointTransformer() = default;
	~PointTransformer() = default;

    template<typename PlaneList>
    void Initialize(const PlaneList& plane);
    [[nodiscard]] bool IsInitialized() const { return m_initialized; }
    [[nodiscard]] Vector3 Transform(const Vector3& p) const;

private:
    Vector3 m_zero;
    Matrix33 m_transformMatrix;
    Matrix33 m_inverseTransformMatrix;
    bool m_initialized{ false };
};

template <typename PlaneList>
void PointTransformer::Initialize(const PlaneList& plane)
{
    auto&& x = plane[2] - plane[0];
    auto&& y = plane[1] - plane[0];

    y = y - x * (x * y / (x * x));
    auto&& z = Cross(x, y);
    x.Normalize();
    y.Normalize();
    z.Normalize();

    m_transformMatrix = Matrix33(
        Vector3(x[0], y[0], z[0]),
        Vector3(x[1], y[1], z[1]),
        Vector3(x[2], y[2], z[2])
    );

    m_inverseTransformMatrix = m_transformMatrix.Inv();

    m_zero = plane[0];

    m_initialized = true;
}
