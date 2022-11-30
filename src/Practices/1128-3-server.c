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

char* creat_chat_space(size_t size, char* begin_address, int flag, int key, int* shm_id)
{
    *shm_id = shmget(key, size, IPC_CREAT | 0644);

    char* start = shmat(*shm_id, begin_address, flag);

    return start;
}

void terminate_conversation(int space_shm_id, char* chat_space, int shm_id_cloud, int* pid_cloud)
{
    shmctl(space_shm_id, IPC_RMID, (void*)0);
    shmdt(chat_space);
    shmctl(shm_id_cloud, IPC_RMID, (void*)0);
    shmdt(pid_cloud);
}

int main(void)
{
    sigset_t usr_mask, commu_mask;
    struct sigaction siga, sigusrone;

    sigfillset(&usr_mask);
    sigfillset(&commu_mask);
    sigdelset(&usr_mask, SIGUSR1);
    sigdelset(&commu_mask, SIGUSR2);
    sigemptyset(&siga.sa_mask);
    siga.sa_flags = 0;
    siga.sa_handler = handler;
    sigemptyset(&sigusrone.sa_mask);
    sigusrone.sa_flags = 0;
    sigusrone.sa_handler = handler;

    sigaction(SIGUSR1, &sigusrone, (struct sigaction*)0);
    printf("This server's pid is %d. Run client with this pid as an argument.", getpid());

    // Waiting for client to retrieve client pid
    sigsuspend(&usr_mask);

    int cloud_shm_id = shmget(512, sizeof(int) * 2, IPC_PRIVATE | 0644);
    if (cloud_shm_id == -1)
    {
        perror("shmget");
        exit(1);
    }

    int* pid_cloud = (int*)shmat(cloud_shm_id, (void*)0, 0);

    // Retrieve the client's pid; pid_cloud[1] is reserved for conversation space address
    pid_t client_pid = pid_cloud[0];

    // Make a room for conversation
    int space_key = 10321;
    int space_shm_id = -1;
    char* space = creat_chat_space(sizeof(char) * 1000, (void*)0, 0, space_key, &space_shm_id);
    pid_cloud[1] = space_key;

    // Send SIGUSR1 to the client process
    printf("Server is waiting for client pid = %d\n", client_pid);
    kill(client_pid, SIGUSR1);

    // Wait SIGUSR1 to receive its response
    sigsuspend(&usr_mask);

    sigaction(SIGUSR2, &siga, (struct sigaction*)0);
    while (1)
    {
        // Input the message which will be sent to the shared memory
        printf("Server > ");
        fscanf(stdin, "%s", space);
        getchar();

        // Type 'q' to halt the conversation
        if (!strcmp(space, "q"))
        {
            puts("Exit this conversation");
            terminate_conversation(space_shm_id, space, cloud_shm_id, pid_cloud);
            kill(client_pid, SIGUSR2);
            break;
        }
        // Wait SIGUSR2 from the client
        kill(client_pid, SIGUSR2);
        sigsuspend(&commu_mask);
        
        // Print retrieved message from the shared memory space
        if (!strcmp(space, "q"))
        {
            puts("The opponent left this space");
            terminate_conversation(space_shm_id, space, cloud_shm_id, pid_cloud);
            break;
        }
        printf("Client : %s", space);
        putchar('\n');
    }

    puts("Bye");
    return 0;
}

