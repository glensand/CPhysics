/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/CPhysics
 */

#pragma once

#include <mutex>
#include <thread>

#include "Point.h"
#include "../ITask.h"

class Pipe;

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
