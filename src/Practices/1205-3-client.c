#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

// Client

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("Not enough arguments\n");
        exit(1);
    }

    int skt = socket(AF_UNIX, SOCK_STREAM, 0);
    struct sockaddr_un sktaddrin;

    sktaddrin.sun_family = AF_UNIX;
    strcpy(sktaddrin.sun_path, "capella_socket");

    if (connect(skt, (struct sockaddr*)&sktaddrin, sizeof(struct sockaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }
    
    if (send(skt, argv[1], sizeof(char) * strlen(argv[1]), 0) == -1)
    {
        perror("send");
        exit(1);
    }

    close(skt);
    return 0;
}