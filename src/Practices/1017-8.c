#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
    int frk = fork();
    if (!frk)
    {
        execl("who", "who", NULL);
    }
    else
    {
        wait((int*)0);
        printf("🇺🇦 Слава Україні! Героям Слава!\n");
    }
    
    return 0;
}