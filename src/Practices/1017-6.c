#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid = fork();

    switch (pid)
    {
        case 0:
            execl("/usr/bin/who", "who", (char*)0);
        case -1:
            perror("fork");
            exit(1);
        default:
            execl("/usr/bin/date", "date", (char*)0);
    }

    return 0;
}