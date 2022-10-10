#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>

bool is_regular_file(struct stat* info)
{
    return (info->st_mode & S_IFMT) == S_IFREG ? true : false;
}

void print_permissions(struct stat* info)
{
    printf("Permission : ");

    for (int i = 0; i <= 6; i += 3)
    {
        if (info->st_mode & (S_IREAD >> i))
            putchar('r');
        else putchar('-');

        if (info->st_mode & (S_IWRITE >> i))
            putchar('w');
        else putchar('-');

        if (info->st_mode & (S_IEXEC >> i))
            putchar('x');
        else putchar('-');
    }
    putchar('\n');
}

mode_t get_new_permissions(const char* new_mode, mode_t mode)
{
    int set_mode = 0, i = 2;

    switch (new_mode[0])
    {
    case 'g':
        while (new_mode[i] != '\0')
        {
            if (new_mode[i] == 'r')
                set_mode |= S_IRGRP;
            else if (new_mode[i] == 'w')
                set_mode |= S_IWGRP;
            else if (new_mode[i] == 'x')
                set_mode |= S_IXGRP;
            i++;
        }
        break;

    case 'u':
        while (new_mode[i] != '\0')
        {
            if (new_mode[i] == 'r')
                set_mode |= S_IXUSR;
            else if (new_mode[i] == 'w')
                set_mode |= S_IWUSR;
            else if (new_mode[i] == 'x')
                set_mode |= S_IXUSR;
            i++;
        }
        break;

    case 'o':
        while (new_mode[i] != '\0')
        {
            if (new_mode[i] == 'r')
                set_mode |= S_IXOTH;
            else if (new_mode[i] == 'w')
                set_mode |= S_IWOTH;
            else if (new_mode[i] == 'x')
                set_mode |= S_IXOTH;
            i++;
        }
        break;
    }

    if (new_mode[1] == '+')
        mode |= set_mode;
    else if (new_mode[1] == '-')
        mode &= ~(set_mode);

    return mode;
}

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        printf("Not enough arguments\n");
        exit(1);
    }
    
    struct stat info;
    stat(argv[2], &info);
    if (!is_regular_file(&info))
    {
        printf("%s is NOT a regular file.\n", argv[2]);
        exit(1);
    }
    print_permissions(&info);

    chmod(argv[2], get_new_permissions(argv[1], info.st_mode));
    stat(argv[2], &info);
    print_permissions(&info);

    return 0;
}