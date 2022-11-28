#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{
    key_t key;
    int shm_id;
    
    shm_id = shmget(1000, 1024, IPC_CREAT | 0644);
    if (shm_id == -1)
    {
        perror("shmget");
        exit(1);
    }

    char* address = (char*)shmat(shm_id, (char*)0, 0);

    for (int i = 0; i < 10; i++)
    {
        strcpy(address, "UNIX");
        sleep(1);
        puts(address);
    }

    shmdt((char*)address);
    shmctl(shm_id, IPC_RMID, (struct shmid_ds*)0);

    return 0;
}