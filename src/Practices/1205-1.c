#include <stdio.h>
#include <netdb.h>

int main(void)
{
    struct servent* port;
    int n;

    scanf("%d", &n);
    port = getservbyport(n, "tcp");

    printf("Port Name : %s, Port : %d\n", port->s_name, port->s_port);

    return 0;
}