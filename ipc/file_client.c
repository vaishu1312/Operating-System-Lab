#include<sys/ipc.h>
#define NULL 0
#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
//#include<sys/wait.h>

void main()
{
char *str;
int id,i;

id=shmget(555,200,IPC_CREAT | 00666);
str=shmat(id,NULL,0);

printf("\nEnter file name: ");
scanf("%s",str);
sleep(10);
printf("\n%s\n",str);
shmdt(str);
shmctl(id,IPC_RMID,NULL);
}
