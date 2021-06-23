/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/CPhysics
 */

#pragma once

#include "Windows.h"

class Pipe final
{
public:

    Pipe()
    {
        hPipe = CreateFile(TEXT("\\\\.\\pipe\\UnityOutPipe"),
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            0,
            NULL);
    }

    template<typename T>
    T Read()
    {
        T result{};

        if (hPipe != INVALID_HANDLE_VALUE)
        {
            unsigned read = 0;
            unsigned toRead = sizeof result;

            auto* buffer = (unsigned char*)&result;

            while (read != toRead)
            {
                DWORD dwRead = 0;

                auto code = ReadFile(hPipe, buffer + read, toRead - read, &dwRead, nullptr);
                if (code == FALSE)
                    break;
                read += dwRead;
            }
        }

        return result;
    }

    void Close()
    {
        CloseHandle(hPipe);
        hPipe = INVALID_HANDLE_VALUE;
    }

private:
    HANDLE hPipe;
};