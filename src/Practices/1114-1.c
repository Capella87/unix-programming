#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        puts("Not enough arguments");
        exit(1);
    }

    int fd = open(argv[1], O_RDWR, 0644);
    if (fd == -1)
    {
        perror(argv[1]);
        exit(1);
    }

    struct flock first_lock, second_lock, third_lock;
    first_lock.l_start = 0; // Start offset
    first_lock.l_len = 4; // Length
    first_lock.l_type = F_WRLCK; // Write Lock
    first_lock.l_whence = SEEK_SET;
    puts("Locking from 0 to 4 (parent)");
    if (fcntl(fd, F_SETLKW, &first_lock) == -1)
    {
        perror("First Lock (parent)");
        exit(1);
    }

    pid_t pid = fork();

    switch (pid)
    {
        case 0: // Child process
            second_lock.l_type = F_WRLCK;
            second_lock.l_len = 4;
            second_lock.l_start = 5;
            second_lock.l_whence = SEEK_SET;

            puts("Locking from 5 to 9 (child)");
            if (fcntl(fd, F_SETLKW, &second_lock) == -1)
            {
                perror("Second Lock (child)");
                exit(1);
            }

            third_lock.l_type = F_WRLCK;
            third_lock.l_len = 4;
            third_lock.l_start = 0;
            third_lock.l_whence = SEEK_SET;

            puts("Locking from 0 to 4 (child)");
            if (fcntl(fd, F_SETLKW, &third_lock) == -1)
            {
                perror("Third Lock (child)");
                exit(1);
            }
            break;
        case -1:
            break;
        default:
            sleep(10);
            
            first_lock.l_type = F_WRLCK;
            first_lock.l_start = 5;
            first_lock.l_len = 4;
            first_lock.l_whence = SEEK_SET;

            puts("Locking from 5 to 9 (parent)");
            if (fcntl(fd, F_SETLKW, &first_lock) == -1)
            {
                perror("Fourth Lock (parent)");
                exit(1);
            }
            
            break;
    }

    return 0;
}