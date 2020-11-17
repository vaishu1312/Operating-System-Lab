#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include <fcntl.h>

void main(int argc, char *argv[])
{
char *source;
char *dest;
char *temp=(char *) malloc(sizeof(char));
char *str=(char *) malloc(sizeof(char)*400); 
int fd1,fd2,n;
if(argc<3)
 printf("\nNot enough arguments!");
else
{
 source=argv[1];
 dest=argv[2]; 
 fd1=open(source,O_RDONLY);
 if(fd1<0)
 {  printf("\nUnable to open %s file",source); exit(1); }
 while(read(fd1,temp,sizeof(char))!=0)
    strcat(str,temp); 
 close(fd1);
 fd2=open(dest,O_WRONLY | O_CREAT);
 if(fd2<0)
  {  printf("\nUnable to open %s file",dest); exit(1); }
 write(fd2,str,strlen(str));  close(fd2); 
 printf("File copied successfully\n"); 
}
}
