#include <stdio.h>
#include <stdlib.h>

#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#include <sys/stat.h>

int wmain(int argc, wchar_t** argv)
{
    int fd;

    _wsopen_s(&fd, L"tmp.bbb", _O_CREAT | _O_WRONLY | _O_TRUNC,
        _SH_DENYNO, _S_IREAD | _S_IWRITE);
    if (fd == -1)
    {
        _wperror(L"Create tmp.bbb");
        exit(1);
    }

    // Reassign fd file descriptor to 1 (Originally Standard output).
    if (_dup2(fd, 1) == -1)
    {
        _wperror(L"Failed to change file descriptor");
        exit(1);
    }

    wprintf(L"DUP2 : Standard Output Redirection\n");
    _close(fd);

    return 0;
}