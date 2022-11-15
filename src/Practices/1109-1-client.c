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
    if (argc < 2)
    {
        printf("Not enough arguments\n");
        exit(1);
    }

    int fd = open(argv[1], O_RDONLY);
    int pfd;
    if (fd == -1)
    {
        perror("open");
        exit(1);
    }

    int retry = 0;
    while (mkfifo("FIFO", 0644) == -1 && retry <= 5)
    {
        remove("FIFO");
        retry++;
    }
    if (retry > 5)
    {
        perror("mkfifo");
        perror("remove");
        exit(1);
    }

    if ((pfd = open("FIFO", O_WRONLY)) == -1)
    {
        perror("open");
        exit(1);
    }

    int n;
    char buffer[257];

    while ((n = read(fd, buffer, 256)) > 0)
    {
        write(pfd, buffer, n);
    }

    close(fd);
    close(pfd);
    return 0;
}