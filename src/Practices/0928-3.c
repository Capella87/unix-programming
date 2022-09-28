#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("Not enough arguments\n");
        exit(1);
    }
    
    DIR* drp;
    struct dirent* dent;

    if ((drp = opendir(argv[1])) == NULL)
    {
        perror(argv[1]);
        exit(1);
    }
    
    int count = 0;

    while ((dent = readdir(drp)))
    {
        if (!strcmp(dent->d_name, ".") || !strcmp(dent->d_name, ".."))
            continue;
        printf("Name: %s\n", dent->d_name);
        printf("Inode: %ld\n", dent->d_ino);
        count++;
    }
    
    closedir(drp);
    return 0;
}