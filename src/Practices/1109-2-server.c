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

    remove("DOWN_FIFO");
    if (mkfifo("DOWN_FIFO", 0644) == -1)
    {
        perror("mkfifo");
        exit(1);
    }

    remove("UP_FIFO");
    if (mkfifo("UP_FIFO", 0644) == -1)
    {
        perror("mkfifo");
        exit(1);
    }

    int down, up;

    write(1, "Connecting to the client...\n\n", 29);
    if ((down = open("DOWN_FIFO", O_WRONLY)) == -1)
    {
        perror("open");
        exit(1);
    }

    if ((up = open("UP_FIFO", O_RDONLY)) == -1)
    {
        perror("open");
        exit(1);
    }

    while (!exit_flag)
    {
        write(1, "Server > ", 9);
        fgets(buffer, MAX_LEN * sizeof(char), stdin);
        if (!strcmp(buffer, "\n"))
        {
            exit_flag = true;
            write(down, "\n", 1);
            write(1, "\n", 1);
            continue;
        }
        write(down, buffer, strlen(buffer));
        
        n = read(up, buffer, MAX_LEN * sizeof(char));
        if (n < 0)
        {
            perror("read");
            exit(1);
        }
        else if (buffer[0] == '\n') break;

        write(1, "Child : ", 8);
        write(1, buffer, n);
        write(1, "\n", 1);
    }

    write(1, "[End of Conversation]\n", 22);
    close(up);
    close(down);
    remove("DOWN_FIFO");
    remove("UP_FIFO");

    return 0;
}