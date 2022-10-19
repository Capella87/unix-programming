#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>
#include <sys/stat.h>
#include <string.h>

int show_files(const char* name, const struct stat* sptr, int type)
{
    if (type == FTW_NS)
    {
        return 0;
    }

    if (type == FTW_F && strstr(name, ".c"))
    {
        printf("%s - %ld\n", name, sptr->st_size);
    }

    return 0;
}

int main(int argc, char** argv)
{
    int show_files(const char*, const struct stat*, int);

    if (argc < 3)
    {
        printf("Not enough arguments\n");
        exit(1);
    }
    ftw(argv[1], show_files, 1);
    

    return 0;
}