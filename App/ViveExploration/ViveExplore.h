#pragma once

#include <thread>

#include "ProducerConsumerQueue.h"
class Pipe;

struct Point final
{
    float x;
    float y;
    float z;
};


#include "../ITask.h"

class ViveExplore : public ITask
{
public:
    ViveExplore() = default;
	virtual ~ViveExplore() override = default;

    virtual void Run(const Params* params = nullptr) override;

private:

    void RunPipeThread();

    std::thread pipeThread;
	Pipe* pipe{ nullptr };
    std::atomic<Point> newPoint;
    std::atomic_flag hasNewPoint;
};
