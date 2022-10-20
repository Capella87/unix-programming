#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main(void)
{
    sigset_t st;

    sigemptyset(&st);

    sigaddset(&st, SIGQUIT);
    sigaddset(&st, SIGILL);
    sigaddset(&st, SIGTRAP);
    int rt;
    if ((rt = sigismember(&st, SIGILL) == 1))
        printf("SIGILL is included in the set\n");
    else if (!rt)
        printf("SIGILL is NOT included in the set\n");
    else
        perror("SIGILL");
    
    return 0;
}