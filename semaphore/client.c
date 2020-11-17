#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/errno.h>
#include <sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<ctype.h>

extern int errno;          
#define SIZE 10 /* size of the shared buffer*/
#define SHMPERM 0666

int segid; /* id for shared memory bufer */
int empty_id;
int full_id;
int mutex_id;

char * buff;
sem_t *empty;
sem_t *full;
sem_t *mutex;
int c=0;
void consume()
{
while (1)
{
if(c>=5)
{
printf("\n Client %d Exited \n",getpid());
exit(1);
}
printf("\nClient %d trying to aquire Semaphore Full \n",getpid());
sem_wait(full);
printf("Client %d successfully aquired Semaphore Full \n",getpid());
printf("Client %d trying to aquire Semaphore Mutex \n",getpid());
sem_wait(mutex);
printf("Client %d successfully aquired Semaphore Mutex\n",getpid());
printf("\nClient %d received Item [ %d ] \n",getpid(),buff[c]);
c++;
sem_post(mutex);
printf("\nClient %d released Semaphore Mutex \n",getpid());
sem_post(empty);
printf("Client %d released Semaphore Empty \n",getpid());
sleep(10);
}
}

int main()
{
segid = shmget(111,50,0);
empty_id=shmget(IPC_PRIVATE,sizeof(sem_t),IPC_CREAT|IPC_EXCL|SHMPERM);
full_id=shmget(IPC_PRIVATE,sizeof(sem_t),IPC_CREAT|IPC_EXCL|SHMPERM);
mutex_id=shmget(IPC_PRIVATE,sizeof(sem_t),IPC_CREAT|IPC_EXCL|SHMPERM);

buff = shmat( segid, NULL, 0 );
empty = shmat(empty_id,(char *)0,0);
full = shmat(full_id,(char *)0,0);
mutex = shmat(mutex_id,(char *)0,0);

sem_init(empty,1,0);
sem_init(full,1,SIZE);
sem_init(mutex,1,1);

consume();

shmdt(buff);
shmdt(empty);
shmdt(full);
shmdt(mutex);
shmctl(segid, IPC_RMID, NULL);
semctl( empty_id, 0, IPC_RMID, NULL);
semctl( full_id, 0, IPC_RMID, NULL);
semctl( mutex_id, 0, IPC_RMID, NULL);
sem_destroy(empty);
sem_destroy(full);
sem_destroy(mutex);
printf("\n Client Exited \n\n");
return(0);
}
