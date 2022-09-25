#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define STR_COUNT 5

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("Invalid argument");
        exit(1);
    }

    int fd;
    off_t cur = 0;
    char buffer[3];

    if ((fd = open("testdata", O_RDONLY)) == -1)
    {
        perror("testdata");
        exit(1);
    }
    off_t end = lseek(fd, 0, SEEK_END);
    cur = lseek(fd, 0, SEEK_SET);
    int interval = atoi(argv[1]);

    // Note: fseek and lseek continue move location beyond the end of file
    printf("Current offset : ");
    do
    {
        printf("%ld ", cur);
    } while ((cur = lseek(fd, interval, SEEK_CUR)) <= end);

    printf("\nCurrent data : ");
    fflush(stdout);
    cur = lseek(fd, 0, SEEK_SET);
    do
    {
        read(fd, buffer, sizeof(char));
        buffer[1] = '\0';
        write(STDOUT_FILENO, buffer, sizeof(char));
        write(STDOUT_FILENO, " ", sizeof(char));
    } while ((cur = lseek(fd, interval - 1, SEEK_CUR)) <= end);
    putchar('\n');
    close(fd);

    return 0;
}