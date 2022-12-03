#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/sem.h>

union semun
{
    int val;
    struct semid_ds* buf;
    unsigned short* array;
    struct seminfo* __buf;
};

int semaphore_init(void)
{
    int semid;
    union semun semunion;

    semid = semget(1000, 1, IPC_CREAT | 0644);
    if (semid == -1)
    {
        perror("semget");
        exit(1);
    }

    semunion.val = 1;
    if (semctl(semid, 0, SETVAL, semunion) == -1)
    {
        perror("semctl - init");
        exit(1);
    }

    return semid;
}

int semaphore_lock(int semid)
{
    struct sembuf buf;

    buf.sem_num = 0;
    buf.sem_op = -1;
    buf.sem_flg = SEM_UNDO;

    // Lock
    if (semop(semid, &buf, 1) == -1)
    {
        perror("semlock failed");
        exit(1);
    }

    return 0;
}

int semaphore_unlock(int semid)
{
    struct sembuf buf;

    buf.sem_num = 0;
    buf.sem_op = 1;
    buf.sem_flg = SEM_UNDO;

    // Unlock
    if (semop(semid, &buf, 1) == -1)
    {
        perror("semunlock failed");
        exit(1);
    }

    return 0;
}

int main(void)
{
    key_t key;
    int shm_id, sem_id;

    sem_id = semaphore_init();
    
    shm_id = shmget(1000, 1024, IPC_PRIVATE | 0644);
    if (shm_id == -1)
    {
        perror("shmget");
        exit(1);
    }

    char* address = (char*)shmat(shm_id, (char*)0, 0);

    for (int i = 0; i < 10; i++)
    {
        semaphore_lock(sem_id);
        strcpy(address, "PROGRAMMING");
        semaphore_unlock(sem_id);

        sleep(1);
        
        semaphore_lock(sem_id);
        puts(address);
        semaphore_unlock(sem_id);
    }

    shmdt((char*)address);
    shmctl(shm_id, IPC_RMID, (struct shmid_ds*)0);

    return 0;
}