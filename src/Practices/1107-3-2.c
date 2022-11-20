// Messenger with FIFO files

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>

void parent(void)
{
    char buffer[257];
    int up, down;

    if ((down = open("DOWN_FIFO", O_WRONLY)) == -1)
    {
        perror("open");
        exit(1);
    }

    if ((up = open("UP_FIFO", O_RDONLY)) == -1)
    {
        perror("open");
        exit(1);
    }

    int n;
    bool stop_flag = false;
    while (!stop_flag)
    {
        write(1, "Parent > ", 9);
        fgets(buffer, 256, stdin);
        if (!strcmp(buffer, "\n"))
            stop_flag = true;
        write(down, buffer, strlen(buffer));
        write(1, "\n", 1);

        n = read(up, buffer, 256);
        write(1, "Child : ", 8);
        write(1, buffer, n);
    }

    close(down);
    close(up);
    wait((void*)0);
}

void child(void)
{
    char buffer[257];
    int up, down;

    if ((down = open("DOWN_FIFO", O_RDONLY)) == -1)
    {
        perror("open");
        exit(1);
    }

    if ((up = open("UP_FIFO", O_WRONLY)) == -1)
    {
        perror("open");
        exit(1);
    }

    int n;
    bool stop_flag = false;
    while (!stop_flag)
    {
        n = read(down, buffer, 256);
        write(1, "Parent : ", 8);
        write(1, buffer, n);

        write(1, "Child > ", 8);
        fgets(buffer, 256, stdin);
        if (!strcmp(buffer, "\n"))
            stop_flag = true;
        write(up, buffer, strlen(buffer));
        write(1, "\n", 1);
    }

    close(down);
    close(up);
}

int main(void)
{
    remove("DOWN_FIFO");
    if (mkfifo("DOWN_FIFO", 0644) == -1)
    {
        perror("mkfifo");
        exit(1);
    }

    remove("UP_FIFO");
    if (mkfifo("UP_FIFO", 0644) == -1)
    {
        perror("mkfifo");
        exit(1);
    }

    pid_t pid;
    switch ((pid = fork()))
    {
        case -1:
            perror("fork");
            exit(1);
        case 0:
            child();
            exit(0);
        default:
            parent();
    }

    remove("DOWN_FIFO");
    remove("UP_FIFO");

    return 0;
}