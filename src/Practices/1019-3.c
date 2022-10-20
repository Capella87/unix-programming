#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void process_sig(int k)
{
    printf("We've received a signal and this function is invoked.\n");
    psignal(k, "Sig");
}

int main(void)
{
    void (*hand)(int);

    if (sigset(SIGQUIT, process_sig) == SIG_ERR)
    {
        perror("sigset");
        exit(1);
    }

    printf("Wait until the signal...\n");
    pause();

    return 0;
}