#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

// Handling SIGINT

struct sigaction act, act2;
sigset_t sig;

void handler(int signo) // SIGINT
{
    sigprocmask(SIG_BLOCK, &sig, (sigset_t*)0);
    psignal(signo, "Received signal:");
    sleep(10);
    sigprocmask(SIG_UNBLOCK, &sig, (sigset_t*)0);
}

void handler2(int signo) // SIGUSR1
{
    psignal(signo, "Received signal:");
    printf("SIGUSR1\n");
    sleep(5);
}

int main(void)
{

    sigemptyset(&act.sa_mask);
    sigemptyset(&act2.sa_mask);
    sigemptyset(&sig);
    sigaddset(&sig, SIGUSR1);
    act.sa_flags = 0;
    act2.sa_flags = 0;
   
    act.sa_handler = handler;
    act2.sa_handler = handler2;
    
    sigaction(SIGINT, &act, (struct sigaction*)0);
    sigaction(SIGUSR1, &act2, (struct sigaction*)0);
    
    while (1)
    {
        pause();
    }

    return 0;
}
