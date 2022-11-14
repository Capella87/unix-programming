#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>

int main(void)
{
    int fd[2];

    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(1);
    }

    // Fork
    pid_t pid = fork();
    switch (pid)
    {
        case -1:
            perror("fork");
            exit(1);
        case 0:
            dup2(fd[0], 0); // Relocate fd[0] (Read) to stdin
            close(fd[1]);

            execlp("/usr/bin/wc", "wc", "-l", (char*)0);
        default:
            dup2(fd[1], 1); // Relocate fd[1] (Write) to stdout
            close(fd[0]);
            
            execlp("/usr/bin/ls", "ls", "-al", (char*)0);
    }

    return 0;
}