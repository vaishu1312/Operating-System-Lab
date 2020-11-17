#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
int fcnt;
char fname [][10];
}Directory;

Directory root;

int checkName(char str[])
{
 int i;
 for(i=0;i<root.fcnt;i++)
   if(strcmp(root.fname[i],str)==0) 
			return i;      
 return i;
}

void main()
{
int i,ch;
char str[10];
root.fcnt=0;
do
{
printf("\n\tSINGLE LEVEL\n");
printf("\n1.Create a file\n2.Delete a file\n3.Search a file\n4.Display all files\n5.Exit\n");
printf("\nEnter your choice: ");
scanf("%d",&ch);
switch(ch)
{
case 1:
      printf("\nEnter file name: ");
      scanf("%s",str);
      if(checkName(str)!=root.fcnt)             
	  			printf("\nFile %s already exists!\n",str);
      else
      {
        strcpy(root.fname[root.fcnt++],str);
        printf("\nFile %s created!\n",str);
      }
      break;
case 2:
      printf("\nEnter file name: ");
      scanf("%s",str);
      i=checkName(str);
      if(i!=root.fcnt)             
	  	{
	  		strcpy(root.fname[i],root.fname[root.fcnt-1]);	
	  		root.fcnt--;
	  		printf("\nFile %s deleted!\n",str);	  			  		
	  	}
      else
				  printf("\nFile %s not found!\n",str);
      break;
case 3:
      printf("\nEnter file name: ");
      scanf("%s",str);
      if(checkName(str)!=root.fcnt)             
	  			printf("\nFile %s exists!\n",str);
      else
	  			printf("\nFile %s does not exists!\n",str);
      break;
case 4:  
				if(root.fcnt==0)
						printf("\nDirectory empty");
				else
				{
       	 printf("\nThe files are: \n\n");
					for(i=0;i<root.fcnt;i++)
					  printf("%s\n",root.fname[i]);  
				}
				break;
}
}while(ch!=5);
}
