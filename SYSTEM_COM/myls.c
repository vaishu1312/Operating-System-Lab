#include<unistd.h>
#include<stdio.h> 
#include<dirent.h>

void main(int argc, char *argv[])
{
char *dname;
struct dirent * d;
if(argc<2)
 printf("\nNot enough arguments!");
else
{
dname=argv[1];
DIR* d1=opendir(dname);
if(d1==NULL)
 printf("\nCant find directory");
else
  while(d=readdir(d1))
     printf("%s\n",d->d_name);
close(d1);
}
}

//d1 represents a directory stream
