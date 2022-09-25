#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    int fd;

    if ((fd = open("residents", O_RDONLY)) == -1)
    {
        perror("residents");
        exit(1);
    }

    char buffer[65];
    int count = 0;
    while (1)
    {
        lseek(fd, count * 64, SEEK_SET);
        if (read(fd, buffer, sizeof(char) * 64) != 64)
            break;

        write(STDOUT_FILENO, buffer, sizeof(char) * strlen(buffer));
        putchar('\n');
        count++;
    }

    close(fd);
    return 0;
}