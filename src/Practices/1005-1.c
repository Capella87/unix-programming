#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv, char** envp)
{
    setenv("HBENV", "hbooks", 1);
    printf("%s\n", getenv("HBENV"));
    
    return 0;
}