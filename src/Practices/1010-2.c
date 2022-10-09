#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int n;

    scanf("%d", &n);

    pid_t pid = fork();

    if (!pid) // Child
    {
        long result = 1;
        for (int i = 1; i <= n; i++)
            result *= i;
        printf("Result = %ld\n", result);
    }
    else // Parent
    {
        long total = 0;
        for (int i = 1; i <= n; i++)
            total += i;
        printf("Total = %ld\n", total);
    }

    return 0;
}