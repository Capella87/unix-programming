#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>

int main(void)
{
    int down[2], up[2];
    char buffer[257];
    int n;

    if (pipe(down) == -1)
    {
        perror("pipe");
        exit(1);
    }
    if (pipe(up) == -1)
    {
        perror("pipe");
        exit(1);
    }

    pid_t pid = fork();
    switch (pid)
    {
        case 0: // Child process
            close(up[0]);
            close(down[1]);

            while (1)
            {
                n = read(down[0], buffer, 256);
                if (n < 0)
                {
                    perror("read");
                    exit(1);
                }
                write(1, "\nParent: ", 9);
                write(1, buffer, n);

                printf("Type (Child): ");
                fgets(buffer, 256, stdin);
                write(up[1], buffer, strlen(buffer));
            }
            exit(0);
        case -1:
            perror("fork");
            exit(1);

        default: // Parent process
            close(up[1]);
            close(down[0]);

            while (1)
            {
                printf("Type (Parent): ");
                fgets(buffer, 256, stdin);
                write(down[1], buffer, strlen(buffer));

                n = read(up[0], buffer, 256);
                if (n < 0)
                {
                    perror("write");
                    exit(1);
                }
                write(1, "\nChild: ", 8);
                write(1, buffer, n);
            }

            wait((void*)0);
            break;
    }

    return 0;
}