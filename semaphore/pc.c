#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <sys/types.h>
#include <unistd.h>

extern int errno;

#define KEY_SM 555
#define KEY_EMPTY 666
#define KEY_FULL 777
#define KEY_MUTEX 888

#define SIZE 20   /* size of the shared buffer*/
#define SHMPERM 00666

int segid;   /* id for shared memory bufer */
int empty_id;
int full_id;
int mutex_id;

int * buff; 
sem_t *empty;
sem_t *full;
sem_t *mutex;

int n=3;

void consume()
{
int c=0;
while (1)
{
if(c>=n)
{
printf("\n Client %d exited \n",getpid());
//wait(NULL);
exit(1); 
}
printf("\nClient %d trying to aquire Semaphore Full \n",getpid());
sem_wait(full);
printf("Client %d successfully aquired Semaphore Full \n",getpid());
printf("Client %d trying to aquire Semaphore Mutex \n",getpid());
sem_wait(mutex);
printf("Client %d successfully aquired Semaphore Mutex\n",getpid());
printf("\nClient %d received Item [ %d ] \n",getpid(),buff[c]);
buff[c]=-1;
c++;
sem_post(mutex);
printf("\nClient %d released Semaphore Mutex \n",getpid());
sem_post(empty);
printf("Client %d released Semaphore Empty \n",getpid());
//sleep(9);
}
}

int main()
{
segid=shmget(KEY_SM,SIZE,IPC_CREAT | IPC_EXCL | SHMPERM);
empty_id=shmget(KEY_EMPTY,sizeof(sem_t),IPC_CREAT | IPC_EXCL | SHMPERM);
full_id=shmget(KEY_FULL,sizeof(sem_t),IPC_CREAT | IPC_EXCL | SHMPERM);
mutex_id=shmget(KEY_MUTEX,sizeof(sem_t),IPC_CREAT | IPC_EXCL | SHMPERM);

buff = shmat(segid, NULL, 0 );
empty = (sem_t *) shmat(empty_id,NULL,0);
full = (sem_t *)shmat(full_id,NULL,0);
mutex = (sem_t *) shmat(mutex_id,NULL,0);

//Initializing Semaphores Empty , Full & Mutex
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
printf("\n Clienti exited \n\n");
return(0);
}


