#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    int fd[2];

    pipe(fd);

    pid_t pid;

    switch(pid = fork())
    {
    case 0: // Child process
        close(fd[1]); // stdout: 1
        dup2(fd[0], 0); // read

        execlp("wc", "wc", "-l", (char*)0);
        break;
    case -1:
        perror("fork");
        exit(1);
    default:
        close(fd[0]); // stdin: 0
        dup2(fd[1], 1); // write

        execlp("ls", "ls", "-al", (char*)0); // Requires command, command argument, other arguments... and (char*)0;
        break;
    }

    return 0;
}