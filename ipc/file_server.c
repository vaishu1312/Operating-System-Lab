#include<sys/ipc.h>
#define NULL 0
#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>

void main()
{
char *str,buf[2];
int id,i,fd;

id=shmget(555,200,IPC_CREAT | 00666);
str=shmat(id,NULL,0);

//wait(NULL);
fd=open(str,O_RDONLY);

if(fd<0)
{
	printf("\nNo such file exists!\n");
	strcpy(str,"Sorry,File does not exist!");
}
else
{ printf("\nFile successfully transferred\n");
	read(fd,str,200);
}
close(fd);
shmdt(str);
}
