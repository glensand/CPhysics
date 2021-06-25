/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/CPhysics
 */

#pragma once

#include "Stream.h"

class Pipe final : public Stream
{
    using HANDLE = void*;
public:

    Pipe();

    // Try to connect to the endpoint, just returns if the connection was already established
    virtual void			Connect() override;

    // Closes connection
    virtual void			Close(ClosingPolicy policy) override;

    // Writes row data to the buffer. Note! this operation block thread
    virtual void			Write(const void* data, unsigned count) override;

    // Reads raw data from the stream, and store it into data. Note! this operation block thread
    virtual void			Read(void* data, unsigned count) override;

    // Reads from the stream the number of bytes, and nothing else
    virtual void			Skip(unsigned size) override;

private:
    HANDLE hPipe;
};