#include <stdio.h>
#include <stdlib.h>

#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <share.h>
#include <sys/stat.h>

void copy_file(int* ofd, int* wfd)
{
    int n = 0;
    wchar_t buffer[256] = L"";

    while ((n = _read(*ofd, (void*)buffer, 256)) > 0)
    {
        if (_write(*wfd, (void*)buffer, n) != n)
        {
            _wperror(L"read");
            break;
        }
    }
}

int wmain(int argc, wchar_t** argv)
{
    int rfd, wfd;

    if (argc < 3)
    {
        wprintf(L"Too few arguments");
        exit(1);
    }

    if (_wsopen_s(&rfd, argv[1], _O_RDONLY, _SH_DENYRW, 0))
    {
        _wperror(argv[1]);
        exit(1);
    }

    if (_wsopen_s(&wfd, argv[2], _O_CREAT | _O_WRONLY | _O_TRUNC, _SH_DENYNO, _S_IREAD | _S_IWRITE))
    {
        _wperror(argv[2]);
        exit(1);
    }

    copy_file(&rfd, &wfd);

    _close(rfd);
    _close(wfd);
    return 0;
}