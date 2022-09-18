#include <stdio.h>
#include <stdlib.h>

#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#include <sys/stat.h>

int wmain(int argc, wchar_t** argv)
{
    int cnt;

    // unlink, _unlink or _wunlink (Windows C Runtime) : Delete a file
    cnt = _wunlink(L"tmp.aaa");
    if (cnt == -1)
    {
        _wperror(L"Unlink tmp.aaa");
        exit(1);
    }
    wprintf(L"Unlink tmp.aaa successfully!\n");

    return 0;
}