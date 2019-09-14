#pragma once

static const double EULER_C{ 2.6 };

class Task
{
public:
	Task() = default;
	virtual ~Task() = default;
	
	virtual void Run() const = 0;
};