#include <stdio.h>
#include <stdlib.h>

#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#include <sys/stat.h>

int wmain(int argc, wchar_t** argv)
{
    int fd, secondfd;

    _wsopen_s(&fd, L"tmp.aaa", _O_CREAT | _O_WRONLY | _O_TRUNC,
        _SH_DENYNO, _S_IREAD | _S_IWRITE);
    if (fd == -1)
    {
        _wperror(L"Create tmp.aaa");
        exit(1);
    }

    // Close the standard output.
    _close(1);
    
    secondfd = _dup(fd);

    wprintf(L"DUP FD=%d\n", secondfd);
    wprintf(L"Standard Output Redirection\n");
    _close(fd);

    return 0;
}