#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/select.h>

#define CHILDREN 2

void parent(int plist[][2])
{
    char buffer[257];
    fd_set set, pmask;

    FD_ZERO(&pmask);
    FD_SET(0, &pmask);

    for (int i = 0; i < CHILDREN; i++)
    {
        close(plist[i][1]);
        FD_SET(plist[i][0], &pmask);
    }
    
    int n;
    while (set = pmask, select(plist[CHILDREN - 1][1] + 1, &set, (fd_set*)0, 
    (fd_set*)0, (struct timeval*)0) > 0)
    {
        for (int i = 0; i < CHILDREN; i++)
        {
            if (FD_ISSET(plist[i][0], &set))
            {
                if ((n = read(plist[i][0], buffer, 256)) > 0)
                {
                    write(1, "Message from child: ", 20);
                    write(1, buffer, n);
                    write(1, "\n", 1);
                }
            }
        }

        // ???
        if (waitpid(-1, (int*)0, WNOHANG) == -1)
            return;
    }
}

void child(int fd[2])
{
    close(fd[0]);
    char buffer[257];

    int n = read(0, buffer, 256);
    if (n < 0)
    {
        perror("read");
        exit(1);
    }
    write(fd[1], buffer, n);
    close(fd[1]);
}

int main(void)
{
    int plist[CHILDREN][2];
    pid_t pid[CHILDREN];

    for (int i = 0; i < CHILDREN; i++)
    {
        if (pipe(plist[i]) == -1)
        {
            perror("pipe");
            exit(1);
        }
        
        pid[i] = fork();
        switch (pid[i])
        {
            case 0:
                child(plist[i]);
                exit(0);
            case -1:
                perror("fork");
                exit(1);
            default:
                break;
        }
    }
    parent(plist);

    return 0;
}