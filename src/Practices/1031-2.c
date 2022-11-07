// Assignments

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>

void handler(int signo)
{
    psignal(signo, "Wake up");
    sleep(1);
    puts("Exit the handler");
}

int main(void)
{
    struct sigaction act;

    sigfillset(&act.sa_mask);
    sigdelset(&act.sa_mask, SIGINT);

    act.sa_handler = handler;
    act.sa_flags = 0;

    sigaction(SIGALRM, &act, (struct sigaction*)0);

    while (1)
    {
        alarm(1);
        pause();
    }

    return 0;
}