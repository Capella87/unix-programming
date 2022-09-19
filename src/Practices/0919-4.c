#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        printf("Not enough arguments\n");
        exit(1);
    }

    // Get guests list from redirection
    char buffers[12][65];
    int r = 0;
    for (int i = 0; i < 12; i++)
    {
        off_t offset = i * 64;
        lseek(STDIN_FILENO, offset, SEEK_SET);
        if ((r = read(STDIN_FILENO, buffers[i], 64)) == -1)
        {
            perror("Error");
            exit(1);
        }
        buffers[i][64] = '\0';
    }

    // Swap rooms between two specified people
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    char temp[65];
    strcpy(temp, buffers[a - 1]);
    strcpy(buffers[a - 1], buffers[b - 1]);
    strcpy(buffers[b - 1], temp);

    // Print guests and their rooms
    for (int i = 0; i < 12; i++)
        printf("%d - %s\n", i + 1, buffers[i]);

    return 0;
}