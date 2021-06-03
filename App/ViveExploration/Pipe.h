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

private:
    HANDLE hPipe;
};