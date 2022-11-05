#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void send(int fd, char* buffer, const char* direction, int i)
{
    int n;

    strcpy(buffer, "hello world #");
    size_t len = strlen(buffer);
    buffer[len] = (char)(i + '0');
    buffer[len + 1] = '\0';
    n = write(fd, buffer, strlen(buffer));

    strcpy(buffer, direction);
    len = strlen(buffer);
    buffer[len] = '\n';
    buffer[len + 1] = '\0';
    n = write(fd, buffer, strlen(buffer));
}

void receive(int fd, char* buffer)
{
    int n;
    for (int i = 0; i < 2; i++)
    {
        n = read(fd, buffer, 255);
        n = write(1, buffer, n);
    }
}

int main(void)
{
    int pps[2][2];
    pid_t pid;
    int n;
    char buffer[256];

    if (pipe(pps[0]) == -1)
    {
        perror("pipe");
        exit(1);
    }

    if (pipe(pps[1]) == -1)
    {
        perror("pipe");
        exit(1);
    }


    switch (pid = fork())
    {
        case -1:
            perror("fork");
            exit(1);
        case 0:     // Child process
            close(pps[0][0]);
            close(pps[1][1]);

            for (int i = 0; i < 3; i++)
            {
                send(pps[0][1], buffer, " (child->parent)", i + 1);
            }
            close(pps[0][1]);
            receive(pps[1][0], buffer);
            close(pps[1][0]);
            break;

        default:
            close(pps[0][1]);
            close(pps[1][0]);

            for (int i = 0; i < 3; i++)
            {
                send(pps[1][1], buffer, " (parent->child)", i + 1);
            }
            close(pps[1][1]);
            receive(pps[0][0], buffer);
            close(pps[0][0]);
            break;
    }

    return 0;
}