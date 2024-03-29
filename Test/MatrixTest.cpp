#include "Test.h"
#include "LinearAlgebra/Matrix33.h"

namespace
{

const Matrix33 AverageMatrix(
    Vector3(1, 4, 5),
    Vector3(5, 1, 4),
    Vector3(11, -4, 7)
);

const auto AverageMatrixDet = -96;

}

TEST(MatrixTest, MultiplicationZeroZeroMatrix)
{
    auto&& result = ZeroMatrix * ZeroMatrix;
    OPEN_ASSERT(result == ZeroMatrix);
}

TEST(MatrixTest, MultiplicationZeroEqualMatrix)
{
    auto&& result = ZeroMatrix * EqualMatrix;
    OPEN_ASSERT(result == ZeroMatrix);
}

TEST(MatrixTest, MultiplicationEqualZeroMatrix)
{
    auto&& result = EqualMatrix * ZeroMatrix;
    OPEN_ASSERT(result == ZeroMatrix);
}

TEST(MatrixTest, MultiplicationEqualEqualMatrix)
{
    auto&& result = EqualMatrix * EqualMatrix;
    OPEN_ASSERT(result == EqualMatrix);
}

TEST(MatrixTest, MultiplicationEqualAverageMatrix)
{
    auto&& result = EqualMatrix * EqualMatrix;
    OPEN_ASSERT(result == EqualMatrix);
}

TEST(MatrixTest, ZeroMatrixDet)
{
    OPEN_ASSERT(ZeroMatrix.Det() == 0);
}

TEST(MatrixTest, EqualMatrixDet)
{
    OPEN_ASSERT(EqualMatrix.Det() == 1);
}

TEST(MatrixTest, AverageMatrixDet)
{
    OPEN_ASSERT(AverageMatrix.Det() == AverageMatrixDet);
}

TEST(MatrixTest, AverageMatrixInverse)
{
    auto&& inv = AverageMatrix.Inv();
    auto&& expectedEqual = inv * AverageMatrix;
    OPEN_ASSERT(expectedEqual == EqualMatrix);
}

