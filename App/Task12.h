#pragma once
#include "ITask.h"

class Task12 : public ITask
{
public:
	virtual ~Task12() = default;
	Task12() = default;

	void Run(const Params* params = nullptr) const override;
};
//------------------------------------------------------------------------------
inline void Task12::Run(const Params* params) const
{
}
