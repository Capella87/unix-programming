#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main(void)
{
    sigset_t st;

    sigfillset(&st);

    int rt;
    if ((rt = sigismember(&st, SIGBUS) == 1))
        printf("SIGBUS is included in the set\n");
    else if (!rt)
        printf("SIGBUS is NOT included in the set\n");
    else
        perror("SIGBUS");
        
    return 0;
}