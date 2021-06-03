#pragma once

#include <mutex>
#include <thread>

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
    std::mutex mu;
    bool added{ false };

    struct PointBuffer
    {
        Point Buffer1;
        Point Buffer2;

        Point* Front{ &Buffer1};
        Point* Back{ &Buffer2 };

        void Swap()
        {
            auto* temp = Front;
            Front = Back;
            Back = temp;
        }
    };

    PointBuffer point;
};
