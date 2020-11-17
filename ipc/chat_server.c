#include<sys/ipc.h>
#define NULL 0
#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

void main()
{
char * str;
char end_str[4]="end";
int id;
id=shmget(111,100, IPC_CREAT | 00666);
str=shmat(id,NULL,0);

printf("\nEnter 'end' to end messaging");
do{
printf("\nMessage from client: %s",str);
//str=" ";
printf("\nEnter your message: ");
fgets(str,100,stdin);
sleep(15);
}while(strcmp(str,end_str)!=10);

shmdt(str);
shmctl(id,IPC_RMID,NULL);
printf("\nChat ended\n");
}
