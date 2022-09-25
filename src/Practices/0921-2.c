#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define STR_COUNT 5

int main(int argc, char** argv)
{
    char str[101] = "";
    int offsets[STR_COUNT + 1] = { 0, };
    int fd;
    int num;

    // Create a file named testdata and open the file
    if ((fd = open("testdata", O_CREAT | O_WRONLY, 0644)) == -1)
    {
        perror("testdata");
        exit(1);
    }

    // Get inputs and write it to the file.
    for (int i = 0; i < STR_COUNT; i++)
    {
        scanf("%[^\n]", str);
        getchar();
        int size = (int)strlen(str);
        write(fd, str, size * sizeof(char));
        offsets[i + 1] = offsets[i] + size;
    }
    close(fd);

    // Open generated file in read-only mode
    if ((fd = open("testdata", O_RDONLY)) == -1)
    {
        perror("datafile");
        exit(1);
    }

    while (1)
    {
        scanf("%d", &num);
        getchar();
        if (num == -1) break;

        // Move the 'cursor' to offsets[num - 1] from the beginning of the file
        lseek(fd, offsets[num - 1], SEEK_SET);
        int size = offsets[num] - offsets[num - 1];
        read(fd, str, sizeof(char) * size);
        str[size] = '\0';
        write(STDOUT_FILENO, str, sizeof(char) * size);
        write(STDOUT_FILENO, "\n", sizeof(char) * 1);
    }

    close(fd);
    return 0;
}