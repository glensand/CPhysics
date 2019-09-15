#pragma once
#include "Task.h"

class Task2 : public Task
{
	Task2() = default;
	virtual ~Task2() = default;

	void Run() const override;
}
;

inline void Task2::Run() const
{
	
}

