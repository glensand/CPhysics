#pragma once

#include "../CPhysics.h"
#include <vector>

namespace CPhysics
{

class IWindow
{
public:
	virtual ~IWindow() = default;
	IWindow() = default;
	virtual std::vector<double> Window(const size_t N) const = 0;
};
	
}