#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
    int fd = open("received.txt", O_CREAT | O_WRONLY, 0644);
    int pfd;
    if (fd == -1)
    {
        perror("open");
        exit(1);
    }

    if ((pfd = open("FIFO", O_RDONLY)) == -1)
    {
        perror("open");
        exit(1);
    }

    int n;
    char buffer[257];

    write(1, "Received contents\n-----------------\n", 37);
    write(fd, "Received contents\n-----------------\n", 37);
    while ((n = read(pfd, buffer, 256)) > 0)
    {
        write(1, buffer, n);
        write(fd, buffer, n);
    }
    write(1, "\n", 1);
    write(fd, "\n", 1);

    close(fd);
    close(pfd);
    return 0;
}