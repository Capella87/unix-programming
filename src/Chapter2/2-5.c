#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

void copy_file(int* rfd, int* wfd)
{
    ssize_t n;
    char buffer[256];

    while (((n = read(*rfd, buffer, 256)) > 0))
    {
        if (write(*wfd, buffer, n) != n)
        {
            perror("read");
            break;
        }
    }
}

int main(int argc, char** argv)
{
    int fd1, fd2;
    
    if (argc < 3)
    {
        perror("Insufficient files");
        exit(1);
    }
    
    fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1)
    {
        perror(argv[1]);
        exit(1);
    }

    fd2 = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd2 == -1)
    {
        perror(argv[2]);
        exit(1);
    }

    copy_file(&fd1, &fd2);
    printf("\nClosing files...\n");
    close(fd1);
    close(fd2);

    return 0;
}