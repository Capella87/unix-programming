#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

// Warning : This code was not ran appropriately on WSL2 Ubuntu 22.04. (kernel 5.15.x)
// This code was ran appropriately on CentOS (Kernel 2.6.x)

struct msgbuf
{
    int mtype;
    char mtext[80];
};

int main(void)
{
    int queue_id = msgget(652, IPC_CREAT | 0644);
    if (queue_id == -1)
    {
        perror("msgget");
        exit(1);
    }

    struct msgbuf postbox;
    struct msgbuf buffer;

    switch (fork())
    {
    case 0:
        buffer.mtype = 1;
        char input[80];
        
        while (1)
        {
            printf("Child > ");
            fgets(input, 80, stdin);
            if (strlen(input) <= 1) break;

            buffer.mtype = 1;
            strcpy(buffer.mtext, input);
            msgsnd(queue_id, &buffer, sizeof(buffer), IPC_NOWAIT);
        }

        strcpy(buffer.mtext, "bye");
        buffer.mtype = 2;
        msgsnd(queue_id, &buffer, sizeof(buffer), 0);

        exit(0);
    default:
        while (1)
        {
            if (msgrcv(queue_id, &postbox, sizeof(postbox), 0, 0) == -1)
                continue;
            printf("Received message : %s\n", postbox.mtext);
            
            if (postbox.mtype == 2) break;
        }
        
        wait((void*)0);
    }

    msgctl(queue_id, IPC_RMID, (void*)0);
    return 0;
}