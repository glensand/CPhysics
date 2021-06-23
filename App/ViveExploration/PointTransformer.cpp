#include "PointTransformer.h"

Vector3 PointTransformer::Transform(const Vector3& p) const
{
    return m_inverseTransformMatrix * p - m_shift;
}
