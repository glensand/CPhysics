#include <cassert>

#include "Test.h"
#include "LinearAlgebra/Matrix33.h"

namespace
{

const Matrix33 ZeroMatrix(
    Vector3(0, 0, 0),
    Vector3(0, 0, 0),
    Vector3(0, 0, 0)
);

const Matrix33 EqualMatrix(
    Vector3(1, 0, 0),
    Vector3(0, 1, 0),
    Vector3(0, 0, 1)
);

}

TEST(MatrixTest, MultiplicationZeroZeroMatrix)
{
    auto&& result = ZeroMatrix * ZeroMatrix;
    assert(result == ZeroMatrix);
}

TEST(MatrixTest, MultiplicationZeroEqualMatrix)
{
    auto&& result = ZeroMatrix * EqualMatrix;
    assert(result == ZeroMatrix);
}

TEST(MatrixTest, MultiplicationEqualZeroMatrix)
{
    auto&& result = EqualMatrix * ZeroMatrix;
    assert(result == ZeroMatrix);
}

TEST(MatrixTest, MultiplicationEqualEqualMatrix)
{
    auto&& result = EqualMatrix * EqualMatrix;
    assert(result == EqualMatrix);
}
