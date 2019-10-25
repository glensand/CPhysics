#pragma once

#include "IWindow.h"

namespace CPhysics
{

class Hanna final : public IWindow
{
public:
	~Hanna() = default;
	Hanna() = default;
	std::vector<double> Window(const size_t N) const override;
};
	
}