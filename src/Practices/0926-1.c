#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("Not enough argument");
        exit(1);
    }

    struct stat buf;
    stat("unix.txt", &buf);
    
    printf("File Name : %s\n", argv[1]);
    printf("Inode Number : %lu\n", buf.st_ino);
    printf("File Type : ");
    
    if (S_ISREG(buf.st_mode))
        printf("Regular File\n");
    else if (S_ISDIR(buf.st_mode))
            printf("Directory\n");
    printf("Permission : ");
    char perm[10] = "------------";

    if ((buf.st_mode & S_IRUSR) != 0)
        perm[1] = 'r';
    if ((buf.st_mode & S_IWUSR) != 0)
        perm[2] = 'w';
    if ((buf.st_mode & S_IXUSR) != 0)
        perm[3] = 'x';
    if ((buf.st_mode & S_IRGRP) != 0)
        perm[4] = 'r';
    if ((buf.st_mode & S_IWGRP) != 0)
        perm[5] = 'w';
    if ((buf.st_mode & S_IXGRP) != 0)
        perm[6] = 'x';
    if ((buf.st_mode & S_IROTH) != 0)
        perm[7] = 'r';
    if ((buf.st_mode & S_IWOTH) != 0)
        perm[8] = 'w';
    if ((buf.st_mode & S_IXOTH) != 0)
        perm[9] = 'x';
        
    printf("%s\n", perm);

    printf("UID : %d\n", buf.st_uid);
    printf("Size : %ld\n", buf.st_size);

    return 0;
}
