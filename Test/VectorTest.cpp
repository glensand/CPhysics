#include "Test.h"
#include "LinearAlgebra/Vector3.h"

namespace
{

const Vector3 ZeroVector(0, 0, 0);
const Vector3 EqualVector(1, 1, 1);
const Vector3 AverageVector1(1, 2, 3);
const Vector3 AverageVector2(4, 11, -10);

}

TEST(VectorTest, DotZeroZeroVector)
{
    auto&& result = ZeroVector * ZeroVector;
    OPEN_ASSERT(result == 0);
}

TEST(VectorTest, DotZeroEqualVector)
{
    auto&& result = ZeroVector * EqualVector;
    OPEN_ASSERT(result == 0);

    result = EqualVector * ZeroVector;
    OPEN_ASSERT(result == 0);
}

TEST(VectorTest, CrossEqualEqualVector)
{
    auto&& result = Cross(EqualVector, EqualVector);
    OPEN_ASSERT(result == ZeroVector);
}

TEST(VectorTest, CrossEqualZeroVector)
{
    auto&& result1 = Cross(EqualVector, ZeroVector);
    OPEN_ASSERT(result1 == ZeroVector);

    auto&& result2 = Cross( ZeroVector, EqualVector);
    OPEN_ASSERT(result2 == ZeroVector);
}

TEST(VectorTest, CrossEqualAverageVector)
{
    const Vector3 Expected1(1, -2, 1);
    auto&& result1 = Cross(EqualVector, AverageVector1);
    OPEN_ASSERT(result1 == Expected1);

    const Vector3 Expected2(-1, 2, -1);
    auto&& result2 = Cross(AverageVector1, EqualVector);
    OPEN_ASSERT(result2 == Expected2);
}

TEST(VectorTest, CrossAverageAverageVector)
{
    auto&& result1 = Cross(AverageVector1, AverageVector1);
    OPEN_ASSERT(result1 == ZeroVector);
}

TEST(VectorTest, CrossAverage1Average2Vector)
{
    auto&& result = Cross(AverageVector1, AverageVector2);
    constexpr Vector3 Expected(-53, 22, 3);
    OPEN_ASSERT(result == Expected);
}