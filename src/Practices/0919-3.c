#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        printf("Not enough arguments");
        exit(1);
    }

    int numbers[1000];
    for (int i = 0; i < 1000; i++)
        numbers[i] = i;
    int fd, num;

    if ((fd = open("numbers.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
    {
        perror("numbers.txt");
        exit(1);
    }
    if (write(fd, numbers, sizeof(numbers)) == -1)
    {
        perror("numbers.txt");
        exit(1);
    }
    close(fd);

    if ((fd = open("numbers.txt", O_RDONLY)) == -1)
    {
        perror("numbers.txt");
        exit(1);
    }

    int start = atoi(argv[1]);
    int range = atoi(argv[2]);

    int cur = lseek(fd, (off_t)start * sizeof(int), SEEK_SET);
    read(fd, numbers, range * sizeof(int));
    for (int i = 0; i < range; i++)
        printf("%d ", numbers[i]);
    putchar('\n');

    close(fd);
    return 0;
}