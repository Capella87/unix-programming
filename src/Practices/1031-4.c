#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, char** argv)
{
    FILE* fp, *fp2;
    char buffer[257] = "";

    fp = popen("more", "w");
    if (!fp)
    {
        fprintf(stderr, "popen is failed");
        exit(1);
    }

    fp2 = fopen(argv[1], "r");
    while (fgets(buffer, 256, fp2))
        fputs(buffer, fp);
    fclose(fp2);
    pclose(fp);
    return 0;
}