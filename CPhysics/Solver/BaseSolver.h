#pragma once

#include "ISolver.h"

namespace CPhysics
{

class BaseSolver : public ISolver
{
public:
			BaseSolver() = default;
	virtual	~BaseSolver() = default;

	bool	SuitableParams(Real leftX, Real rightX) const override;

};

}

