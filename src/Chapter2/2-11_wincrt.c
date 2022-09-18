#include <stdio.h>
#include <stdlib.h>

#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#include <sys/stat.h>

int wmain(int argc, wchar_t** argv)
{
    int fd;

    // _commit : Somewhat similar to fsync(1) in POSIX
    _wsopen_s(&fd, argv[1], _O_CREAT | _O_WRONLY | _O_TRUNC, _SH_DENYNO, _S_IREAD | _S_IWRITE);

    _write(fd, L"This is test string. 이것은 테스트 문자열입니다.", 37);

    if (_commit(fd) == -1)
    {
        _wperror(argv[1]);
        exit(1);
    }
    wprintf(L"Commit strings in memory to %s successfully!\n", argv[1]);

    return 0;
}