#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, char** argv)
{
    int fd[2];
    char buffer[257] = "";
    pid_t pid;
    int status, n;

    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(1);
    }

    switch(pid = fork())
    {
    case 0:
        execlp("more", "more", buffer, (char*)0);
        break;
    case -1:
        perror("fork");
        exit(1);
    default:
        wait(&status);
        while ((n = read(fd[0], buffer, 256)) > 0)
            write(stdout, buffer, n);
        putchar('\n');
        break;
    }

    return 0;
}