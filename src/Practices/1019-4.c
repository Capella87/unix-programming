#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void process_sig(int k)
{
    printf("We've received a signal and this function is invoked\n");
    psignal(k, "Sig");
}

int main(void)
{
    struct sigaction act;

    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGQUIT);
    act.sa_flags = SA_SIGINFO;
    act.sa_flags = SA_RESETHAND;
    act.sa_handler = process_sig;

    if (sigaction(SIGQUIT, &act, (struct sigaction*)NULL) < 0)
    {
        perror("sigaction");
        exit(1);
    }

    printf("Wait until the signal...\n");
    pause();


    printf("Wait until the signal...\n");
    pause();
    return 0;
}