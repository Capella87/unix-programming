#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void print_file_type(struct stat* info)
{
    printf("File Type : ");
    if (S_ISFIFO(info->st_mode))
        puts("FIFO File");
    else if (S_ISDIR(info->st_mode))
        puts("Directory");
    else if (S_ISREG(info->st_mode))
        puts("Regular File");
    else if (S_ISLNK(info->st_mode))
        puts("Symbolic Link");
    else puts("ETC file");
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

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("An argument is not specified\n");
        exit(1);
    }

    printf("File Name : %s\n", argv[1]);
    struct stat info;

    stat(argv[1], &info);
    printf("Inode Number : %lu\n", info.st_ino);
    print_file_type(&info);
    print_permissions(&info);
    printf("UID : %d\n", info.st_uid);
    printf("Size : %ld\n", info.st_size);

    return 0;
}