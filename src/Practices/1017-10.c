#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
    char* lst[] = { "who", "who", (char*)0 };
    int frk = fork();
    int status = 0;
    if (!frk)
    {
        execvp(lst[0], lst + 1);
    }
    else
    {
        char* cities[] = { "Kherson", "Donetsk", "Luhansk", "Simferopol", "Sevastopol", "Melitopol", "Enerhodar" };
        while (waitpid(frk, &status, WNOHANG) == 0)
        {
            for (int i = 0; i < 7; i++)
            {
                printf("Restoring %s from Russia...\n", cities[i]);
            }
        }
        printf("🇺🇦 Слава Україні! Героям Слава!\n");
    }
    return 0;
}