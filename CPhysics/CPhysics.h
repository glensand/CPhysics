#pragma once

namespace CPhysics
{

using Real = double;

typedef Real(*OneDimensionalFunction)(Real x);

struct Params
{
	virtual ~Params() = default;
};

}
