#include <iostream>
#include <Windows.h>
using namespace std;

void copy_file(HANDLE* ofd, HANDLE* wfd)
{
    wchar_t buffer[256] = L"";
    DWORD read_count = 0;
    DWORD written_count = 0;
    
    while (ReadFile(*ofd, buffer, 256, &read_count, NULL) && read_count > 0)
        if (WriteFile(*wfd, buffer, read_count, &written_count, NULL) && written_count != read_count)
            break;
}

int wmain(int argc, wchar_t** argv)
{
    if (argc < 3)
    {
        wchar_t errBuffer[1000];
        wprintf(L"Too few arguments.");
        exit(1);
    }

    HANDLE ofd = CreateFileW(argv[1], GENERIC_READ, 0, NULL, OPEN_EXISTING, 
        FILE_ATTRIBUTE_NORMAL, NULL);
    if (ofd == INVALID_HANDLE_VALUE)
    {
        wchar_t errBuffer[1000];
        FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, ofd, ERROR_FILE_NOT_FOUND, 0, errBuffer, 1000, NULL);
        printf("%ws: %ws", argv[1], errBuffer);
        exit(1);
    }
    HANDLE wfd = CreateFileW(argv[2], GENERIC_WRITE, 0, NULL, CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL, NULL);
    if (wfd == INVALID_HANDLE_VALUE)
    {
        wchar_t errBuffer[1000];
        FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, ofd, ERROR_INVALID_OPERATION, 0, errBuffer, 1000, NULL);
        printf("%ws: %ws", argv[2], errBuffer);
        exit(1);
    }

    copy_file(&ofd, &wfd);
    CloseHandle(&ofd);
    CloseHandle(&wfd);

    return 0;
}