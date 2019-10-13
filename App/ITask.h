#pragma once

static const double EULER_C{ 2.6 };

struct Params
{
	Params() = default;
	virtual ~Params() = default;
};

class ITask
{
public:
	
	ITask() = default;
	virtual ~ITask() = default;
	
	virtual void Run(const Params* params = nullptr) const = 0;
};