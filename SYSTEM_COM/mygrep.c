#include<stdio.h>
#include<unistd.h>
#include <fcntl.h>
#include<string.h>
#include<stdlib.h>
//search in text.txt
void main(int argc, char *argv[])
{
char *file;
char *pat; 
int fd1;
char *temp=(char *) malloc(sizeof(char));
char *str=(char *) malloc(sizeof(char)*200); 
if(argc<3)
{ printf("\nNot enough arguments!"); exit(1); }
pat=argv[1];
file=argv[2]; 
fd1=open(file,O_RDONLY);
if(fd1<0)
{  printf("\nUnable to open %s file",file); exit(1); }
while(read(fd1,temp,sizeof(char))!=0)
{ 
  if(*temp!='\n')
     strcat(str,temp); 
  else
  {  if(strstr(str,pat))
         printf("%s\n",str);  
     strcpy(str, ""); 
  }
}
close(fd1);
}

/*
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main(int argc , char* argv[])
{
char * fname,*pattern;
char *str=(char *)malloc(200*sizeof(char));
char *temp=(char *)malloc(sizeof(char));
int fd;
if(argc!=3)
{  printf("\nInsufficient no of arguments\n");
   exit(0);
}
pattern=argv[1];
fname=argv[2];
fd=open(fname,O_RDONLY);
if(fd<0)
{ printf("\nFile does not exist\n"); exit(1);  }
int cnt=0;
while( read(fd,temp,sizeof(char)) !=0)
{ 	
 if(*temp!='\n')
 {  strcat(str,temp);   }
 else
 { cnt++;
   if(strstr(str,pattern))
   {	printf("%d. %s\n",cnt,str);  }
   str=(char *)malloc(200*sizeof(char));
 }
}
return 0;
}
*/

