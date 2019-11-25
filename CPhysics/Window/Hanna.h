#pragma once

#include "IWindow.h"

namespace CPhysics
{

class Hanna final : public IWindow
{
public:
	virtual ~Hanna() = default;
			Hanna() = default;

	[[nodiscard]] std::vector<Real>	Window(const size_t N) const override;
};
	
}