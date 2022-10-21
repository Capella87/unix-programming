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
    if (!frk)
    {
        execvp(lst[0], lst + 1);
    }
    else
    {
        wait((int*)0);
        printf("🇺🇦 Слава Україні! Героям Слава!\n");
    }
    return 0;
}