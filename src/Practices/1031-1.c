#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/syscall.h>

int main(void)
{
    sigset_t n;

    sigemptyset(&n);
    sigaddset(&n, SIGINT);
    sigprocmask(SIG_BLOCK, &n, (sigset_t*)0);

    while (1)
    {
        puts("UNIX Programming");
        sleep(1);
    }

    return 0;
}