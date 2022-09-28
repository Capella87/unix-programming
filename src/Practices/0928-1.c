#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>

int main(int argc, char** argv)
{
    struct stat buf, target;
    const char* filename = "unix.txt";
    stat(filename, &buf);
    char target_name[101];
    
    link(filename, "unix1.ln");
    link(filename, "unix2.ln");
    symlink(filename, "unix1.sym");
    symlink(filename, "unix2.sym");

    scanf("%[^\n]", target_name);
    if (stat(target_name, &buf) == -1)
    {
        perror(target_name);
        exit(1);
    }

    char* extension;
    char buffer[257];
    if ((extension = strstr(target_name, ".ln")))
    {
        if (lstat(target_name, &target) == -1)
        {
            perror("lstat");
            exit(1);
        }
        printf("%s\n", target_name);
        printf("Inode: %ld\n", target.st_ino);
        printf("Links: %ld\n", target.st_nlink);
        realpath(target_name, buffer);
        printf("Original Path: %s\n", buffer);
    }
    else if ((extension = strstr(target_name, ".sym")))
    {
        if (stat(target_name, &target) == -1)
        {
            perror("stat");
            exit(1);
        }
        printf("%s\n", target_name);
        printf("%ld\n", target.st_ino);
        printf("%ld\n", target.st_nlink);
    }

    return 0;
}
