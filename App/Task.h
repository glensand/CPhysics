#pragma once

static const double EULER_C{ 2.6 };

struct Params
{
	Params() = default;
	virtual ~Params() = default;
};

class Task
{
public:
	
	Task() = default;
	virtual ~Task() = default;
	
	virtual void Run(const Params* params = nullptr) const = 0;
};