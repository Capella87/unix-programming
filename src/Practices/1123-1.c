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

struct msgbuf
{
    long mtype;
    char mtext[80];
};

int main(void)
{
    int queue_id = msgget(517, IPC_CREAT | 0644);
    
    struct msgbuf buffer, buffer2, buffer3, buffer4;
    buffer.mtype = 1;
    strcpy(buffer.mtext, "Test Message 1");

    buffer2.mtype = 3;
    strcpy(buffer2.mtext, "Test Message 3-1");
    
    buffer3.mtype = 3;
    strcpy(buffer3.mtext, "Test Message 3-2");

    msgsnd(queue_id, &buffer, sizeof(buffer), 0);
    msgsnd(queue_id, &buffer2, sizeof(buffer2), 0);
    msgsnd(queue_id, &buffer3, sizeof(buffer3), 0);

    ssize_t len = msgrcv(queue_id, &buffer4, sizeof(buffer4), 3, 0);

    printf("Received Message : %s\n", buffer4.mtext);

    return 0;
}