#include <sys/ipc.h>
# define NULL 0
#include <sys/shm.h>
#include <sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/wait.h>
#include <stdio_ext.h>
#include<ctype.h>

void main()
{
int pid;
char *a,*b;
char name[50];
int id,i;

id=shmget(IPC_PRIVATE,50,IPC_CREAT | 00666);
pid=fork();

if(pid>0)  //in parent
{
  a=shmat(id,NULL,0);
  printf("\nEnter a name: ");
  scanf("%s",a);
  wait(NULL);
  shmdt(a);
}

else  //in child
{
  sleep(10);
	b=shmat(id,NULL,0);
	strcpy(name,b);
	for(i=0;name[i]!='\0';i++)
  	name[i]=toupper(name[i]);
	printf("\nUpper case: %s\n",name);
	shmdt(b);
}
}

/*
void main()
{
char *b,*a,name[50];
int id,pid,i;

id=shmget(IPC_PRIVATE,50,IPC_CREAT|00666);
a=shmat(id,NULL,0);

printf("\nEnter a name: ");
scanf("%s",a);
shmdt(a);

pid = fork();

if(pid==0) //in child
{ 
	b=shmat(id,NULL,0);
	strcpy(name,b);
	for(i=0;name[i]!='\0';i++)
 	 name[i]=toupper(name[i]);
	printf("\nUpper case: %s\n",name);
	shmdt(b);
}
else
  wait(NULL);
}
*/
