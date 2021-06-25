#include "Pipe.h"
#include "Windows.h"

Pipe::Pipe()
{
    hPipe = INVALID_HANDLE_VALUE;
}

void Pipe::Connect()
{
    hPipe = CreateFile(TEXT("\\\\.\\pipe\\UnityOutPipe"),
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);
}

void Pipe::Close(ClosingPolicy policy)
{
    CloseHandle(hPipe);
    hPipe = INVALID_HANDLE_VALUE;
}

void Pipe::Write(const void* data, unsigned count)
{

}

void Pipe::Read(void* data, unsigned count)
{
    if (hPipe != INVALID_HANDLE_VALUE)
    {
        unsigned read = 0;
        unsigned toRead = count;

        auto* buffer = (unsigned char*)data;

        while (read != toRead)
        {
            DWORD dwRead = 0;

            auto code = ReadFile(hPipe, buffer + read, toRead - read, &dwRead, nullptr);
            if (code == FALSE)
                break;
            read += dwRead;
        }
    }
}

void Pipe::Skip(unsigned size)
{

}
