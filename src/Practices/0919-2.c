#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("Not enough arguments");
        exit(1);
    }

    int fd;

    if ((fd = open("residents", O_RDONLY)) == -1)
    {
        perror("residents");
        exit(1);
    }

    off_t end = lseek(fd, 0, SEEK_END);
    off_t offset = (atoi(argv[1]) - 1) * 64;
    char buffer[65];
    if (offset > end)
        exit(1);

    lseek(fd, offset, SEEK_SET);
    read(fd, buffer, sizeof(char) * 64);
    buffer[64] = '\0';
    write(STDOUT_FILENO, buffer, sizeof(char) * strlen(buffer));

    close(fd);
    return 0;
}