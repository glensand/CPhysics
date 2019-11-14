#pragma once

#include "ITask.h"

class Task9 : public ITask
{
public:

	Task9() = default;
	virtual ~Task9() = default;

	void Run(const Params* params) const override;
};

inline void Task9::Run(const Params* params) const
{
}
