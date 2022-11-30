#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void handler(int signo)
{
    psignal(signo, "Received signal");
}

char* get_chat_space(size_t size, char* begin_address, int flag, int key, int* shm_id)
{
    *shm_id = shmget(key, size, 0);
    char* space = shmat(*shm_id, begin_address, 0);

    return space;
}

void terminate_conversation(char* chat_space, int* pid_cloud)
{
    shmdt(chat_space);
    shmdt(pid_cloud);
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("Not enough arguments\n");
        exit(1);
    }

    pid_t parent_pid = (pid_t)atoi(argv[1]);
    struct sigaction siga, sigusrone;
    sigset_t usr1, usr2;

    sigfillset(&usr1);
    sigfillset(&usr2);
    sigdelset(&usr1, SIGUSR1);
    sigdelset(&usr2, SIGUSR2);
    sigemptyset(&siga.sa_mask);
    siga.sa_flags = 0;
    siga.sa_handler = handler;
    sigemptyset(&sigusrone.sa_mask);
    sigusrone.sa_flags = 0;
    sigusrone.sa_handler = handler;


    int cloud_shm_id = shmget(512, sizeof(int) * 2, IPC_CREAT | 0644);
    if (cloud_shm_id == -1)
    {
        perror("shmget");
        exit(1);
    }

    int* pid_cloud = (int*)shmat(cloud_shm_id, (void*)0, 0);

    pid_cloud[0] = getpid();

    kill(parent_pid, SIGUSR1);
    sigaction(SIGUSR1, &sigusrone, (struct sigaction*)0);
    sigsuspend(&usr1);
    

    int space_key = pid_cloud[1];
    int space_shm_id = -1;
    char* space = get_chat_space(sizeof(char) * 1000, (void*)0, 0, space_key, &space_shm_id);
    kill(parent_pid, SIGUSR1);

    sigaction(SIGUSR2, &siga, (struct sigaction*)0);
    sigsuspend(&usr2);
    while (1)
    {
        if (!strcmp(space, "q"))
        {
            puts("The opponent left this space");
            terminate_conversation(space, pid_cloud);
            break;
        }
        printf("Server : %s", space);
        putchar('\n');

        printf("Client > ");
        fscanf(stdin, "%s", space);
        getchar();

        // Type 'q' to halt the conversation
        if (!strcmp(space, "q"))
        {
            puts("Exit this conversation");
            terminate_conversation(space, pid_cloud);
            kill(parent_pid, SIGUSR2);
            break;
        }
        // Wait SIGUSR2 from the client
        kill(parent_pid, SIGUSR2);
        sigsuspend(&usr2);
    }

    return 0;
}