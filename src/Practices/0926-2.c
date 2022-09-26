#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        printf("Not enough arguments\n");
        exit(1);
    }

    struct stat info;

    stat(argv[2], &info);
    char perm[11] = "----------";
    if (!S_ISREG(info.st_mode))
    {
        printf("Argument object is not a file\n");
        exit(1);
    }
    
    if ((info.st_mode & S_IRUSR) != 0)
        perm[1] = 'r';
    if ((info.st_mode & S_IWUSR) != 0)
        perm[2] = 'w';
    if ((info.st_mode & S_IXUSR) != 0)
        perm[3] = 'x';
    if ((info.st_mode & S_IRGRP) != 0)
        perm[4] = 'r';
    if ((info.st_mode & S_IWGRP) != 0)
        perm[5] = 'w';
    if ((info.st_mode & S_IXGRP) != 0)
        perm[6] = 'x';
    if ((info.st_mode & S_IROTH) != 0)
        perm[7] = 'r';
    if ((info.st_mode & S_IWOTH) != 0)
        perm[8] = 'w';
    if ((info.st_mode & S_IXOTH) != 0)
        perm[9] = 'x';
    printf("%s\n", perm);

    int x = 0;
    switch (argv[1][0])
    {
        case 'g':
            switch (argv[1][2])
            {
                case 'x':
                    x = S_IXGRP;
                    break;
                case 'r':
                    x = S_IRGRP;
                    break;
                case 'w':
                    x = S_IWGRP;
                    break;
            }
            break;

        case 'u':
            switch (argv[1][2])
            {
                case 'x':
                    x = S_IXUSR;
                    break;
                case 'r':
                    x = S_IRUSR;
                    break;
                case 'w':
                    x = S_IWUSR;
                    break;
            }
            break;
        case 'o':
            switch (argv[1][2])
            {
                case 'x':
                    x = S_IXOTH;
                    break;
                case 'r':
                    x = S_IROTH;
                    break;
                case 'w':
                    x = S_IWOTH;
                    break;
            }
            break;
    }
    
    if (argv[1][1] == '+')
    {
        info.st_mode |= x;
    }
    else
    {
        info.st_mode &= ~(x);
    }
    chmod(argv[2], info.st_mode);

    return 0;
}