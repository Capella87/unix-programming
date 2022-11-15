#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>

void handler(int signo)
{
    printf("Signal is detected\n");
    psignal(signo, "Received");
}

int main(void)
{
    struct sigaction act;

    sigfillset(&act.sa_mask);
    sigdelset(&act.sa_mask, SIGINT);
    act.sa_flags = 0;
    act.sa_handler = handler;

    sigaction(SIGINT, &act, (struct sigaction*)0);
    pause();

    return 0;
}