#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 256

int main(void)
{
    char buffer[MAX_LEN + 1];
    bool exit_flag = false;
    int n;

    int down, up;

    write(1, "Connecting to the server...\n\n", 29);
    if ((down = open("DOWN_FIFO", O_RDONLY)) == -1)
    {
        perror("open");
        exit(1);
    }

    if ((up = open("UP_FIFO", O_WRONLY)) == -1)
    {
        perror("open");
        exit(1);
    }

    while (!exit_flag)
    {   
        n = read(down, buffer, MAX_LEN * sizeof(char));
        if (n < 0)
        {
            perror("read");
            exit(1);
        }
        if (buffer[0] == '\n') break;

        write(1, "Parent : ", 9);
        write(1, buffer, n);

        write(1, "Child > ", 8);
        fgets(buffer, MAX_LEN * sizeof(char), stdin);
        if (!strcmp(buffer, "\n"))
        {
            exit_flag = true;
            write(up, "\n", 1);
            write(1, "\n", 1);
            continue;
        }

        write(up, buffer, strlen(buffer));
        write(1, "\n", 1);
    }

    write(1, "[End of Conversation]\n", 22);
    close(up);
    close(down);
    remove("DOWN_FIFO");
    remove("UP_FIFO");

    return 0;
}