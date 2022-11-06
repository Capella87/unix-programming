// Assignment

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("Not enough arguments\n");
        exit(1);
    }
#ifdef TIMES
    struct timeval stime, etime;
    long time_result;
#endif

    int fd;

    if ((fd = open(argv[1], O_RDONLY, 0644)) == -1)
    {
        perror("open");
        exit(1);
    }


    pid_t pid;

    switch ((pid = fork()))
    {
        case -1:
            perror("fork");
            exit(1);

        case 0:
        #ifdef TIMES
            gettimeofday(&stime, NULL);
        #endif

            int buf = 0;
            for (int i = 0; i < 512; i++)
            {
                int n = read(fd, &buf, sizeof(int));
                printf("%d ", buf);
            }
            putchar('\n');

        #ifdef TIMES
            gettimeofday(&etime, NULL);
            time_result = etime.tv_usec - stime.tv_usec;
            printf("Execution Time (child): %ld ms\n", time_result);
        #endif

            break;

        default:
            wait((int*)0);
        #ifdef TIMES
            gettimeofday(&stime, NULL);
        #endif

            int buf2 = 0;
            for (int i = 0; i < 512; i++)
            {
                int n = read(fd, &buf2, sizeof(int));
                printf("%d ", buf2);
            }
            putchar('\n');

        #ifdef TIMES
            gettimeofday(&etime, NULL);
            time_result = etime.tv_usec - stime.tv_usec;
            printf("Execution Time (parent): %ld ms\n", time_result);
        #endif
            break;
    }

    close(fd);
    return 0;
}