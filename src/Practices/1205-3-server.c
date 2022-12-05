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

// Server

int main(int argc, char** argv)
{
    int skt = socket(AF_UNIX, SOCK_STREAM, 0);
    struct sockaddr_un sktaddrin, client;
    int client_len;
    char buffer[257];

    sktaddrin.sun_family = AF_UNIX;
    strcpy(sktaddrin.sun_path, "capella_socket");
    unlink("capella_socket");
    bind(skt, (struct sockaddr*)&sktaddrin, sizeof(struct sockaddr));

    if (listen(skt, 1) <= -1)
    {
        perror("listen");
        exit(1);
    }

    int clientid;

    if ((clientid = accept(skt, (struct sockaddr*)&client, &client_len)) == -1)
    {
        perror("accept");
        exit(1);
    }

    if (recv(clientid, buffer, 256, 0) == -1)
    {
        perror("recv");
        exit(1);
    }

    int fd = open(buffer, O_RDONLY), read_count;
    if (fd == -1)
    {
        perror("open");
        exit(1);
    }

    while ((read_count = read(fd, buffer, 256)) > 0)
    {
        write(1, buffer, read_count);
    }
    write(1, "\n", 1);

    close(skt);
    close(clientid);
    close(fd);
    return 0;
}