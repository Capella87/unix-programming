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

    if ((fd = fopen("testdata", "r")) == NULL)
    {
        perror("testdata");
        exit(1);
    }
    fseek(fd, 0, SEEK_END);
    off_t end = ftell(fd);
    fseek(fd, 0, SEEK_SET);
    cur = ftell(fd); // Use ftell to get current location
    int interval = atoi(argv[1]);

    // fseek returns 0 if it successfully moved location
    printf("Current offset : ");
    do
    {
        printf("%ld ", ftell(fd));
        fseek(fd, interval, SEEK_CUR);
    } while (ftell(fd) <= end);

    // Use fflush to print a string immediately
    printf("\nCurrent data : ");
    fflush(stdout);
    fseek(fd, 0, SEEK_SET);
    cur = ftell(fd);
    do
    {
        // fread(buffer, size, count, file_pointer);
        fread(buffer, sizeof(char), 1, fd);
        buffer[1] = '\0';
        fwrite(buffer, sizeof(char), 1, stdout);
        fwrite(" ", sizeof(char), 1, stdout);
        fseek(fd, interval - 1, SEEK_CUR);
    } while (ftell(fd) <= end);
    putchar('\n');
    fclose(fd);

    return 0;
}