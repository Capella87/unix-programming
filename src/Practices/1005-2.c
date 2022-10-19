#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv, char** envp)
{
    if (argc < 3)
    {
        printf("Not enough arguments\n");
        exit(1);
    }

    setenv(argv[1], argv[2], 1);

    printf("%s\n\n", getenv(argv[1]));
    char** envs = envp;
    while (*envs)
    {
        printf("%s\n", *(envs++));
    }
    return 0;
}