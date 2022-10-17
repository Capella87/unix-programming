#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("Not enough arguments\n");
        exit(1);
    }
    int fd = open(argv[1], O_RDONLY, 0644);

    if (fd == -1)
    {
        perror(argv[1]);
        exit(1);
    }

    char buff[11];
    int n = read(fd, buff, 10);
    printf("Current position: %ld\n", lseek(fd, 0, SEEK_CUR));
    int frk = fork();

    if (!frk) // Child process
    {
        n = read(fd, buff, 10);
        printf("Current position: %ld\n", lseek(fd, 0, SEEK_CUR));
    }
    else
    {
        wait((int*)0);
        printf("Current position: %ld\n", lseek(fd, 0, SEEK_CUR));
    }

    return 0;
}