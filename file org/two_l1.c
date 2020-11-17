//two separate structs
//final
//delete directory not done

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

typedef struct Sub_dir ufd;  //ufd--user file directory

typedef struct{
int fcnt;
char fname [][10];
}File;

struct Sub_dir{
char dname[10];
ufd* next;
File f;
};

ufd* head=NULL;
int no_dir=0;

int checkName(char str[],ufd* ptr)
{
 int i;
 for(i=0;i<ptr->f.fcnt;i++)
   if(strcmp(ptr->f.fname[i],str)==0) 
			return i;    
 return i;
} 

ufd * checkDirName(char str[])
{
 ufd* temp=head;
 int i;
 for(i=0;i<no_dir;i++)
 { if(strcmp(temp->dname,str)==0)
			  break;
	 temp=temp->next;
 } 		
 return temp;
}


int main()
{
int i,j,ch;
char str[10],fstr[10];
ufd* temp,*ptr,*new1;
do
{
printf("\n\nTWO-LEVEL ORGANIZATION\n");
printf("\n1.Create a directory\n2.Create a file\n3.Delete a file\n4.Search a file\n5.Display all files\n6.Exit\n");
printf("\nEnter your choice: ");
scanf("%d",&ch);

switch(ch)
{
case 1:
      printf("\nEnter directory name: ");
      scanf("%s",str); 
      if(checkDirName(str)!=NULL)             
	  			printf("\nDirectory %s  already exists!\n",str);
      else
      {
				new1=(ufd*)malloc(sizeof(ufd));
        strcpy(new1->dname,str);
        new1->f.fcnt=0; 		new1->next=NULL;
        no_dir++;
				if(head==NULL)
 	  			 head=new1;
			  else
			  {  
	       new1->next=head;	
			   head=new1; 
			  }
			  printf("\nDirectory %s created!\n",new1->dname);
      }
      break;


case 2:
      printf("\nEnter the directory in which you want to create the file: ");
      scanf("%s",str);
      temp=checkDirName(str);
      if(temp==NULL)
      { 
      	printf("\nNo such directory!\n"); 
        break;  
      }    
      printf("\nEnter file name: ");
      scanf("%s",fstr);
      if(checkName(fstr,temp)!=temp->f.fcnt)             
	  			printf("\nFile %s already exists in directory %s!\n",fstr,temp->dname);
      else
      { 
        strcpy(temp->f.fname[temp->f.fcnt++],fstr);
        printf("\nFile %s created in directory %s!\n",temp->f.fname[temp->f.fcnt-1],temp->dname);
      }
      break;
      
case 3:
      printf("\nEnter the directory name: ");
      scanf("%s",str);
      temp=checkDirName(str);
      if(temp==NULL)
      { 
      	printf("\nNo such directory!\n"); 
        break;  
      }      
      printf("\nEnter file name: ");
      scanf("%s",fstr);
      i=checkName(fstr,temp);
      if(i!=temp->f.fcnt)             
	  	{
       strcpy(temp->f.fname[i],temp->f.fname[--temp->f.fcnt]);	  		
	  	 printf("\nFile %s deleted from directory %s!\n",fstr,temp->dname);	  
	  	}
      else
 			   printf("\nFile %s not found in directory %s!\n",fstr,temp->dname);
 			break;
      
case 4:
      printf("\nEnter the directory name: ");
      scanf("%s",str);
      temp=checkDirName(str);
      if(temp==NULL)
      { 
      	printf("\nNo such directory!\n"); 
        break;  
      }    
      printf("\nEnter file name: ");
      scanf("%s",fstr);
      if(checkName(fstr,temp)!=temp->f.fcnt)             
      	 printf("\nFile %s exists in directory %s!\n",fstr,temp->dname);	  
	  	else
 			   printf("\nFile %s not found in directory %s!\n",fstr,temp->dname);
       break;
            
case 5:  
        printf("\n\tDIRECTORY\tFILES\n");
				ptr=head;
				for(i=0;i<no_dir;i++)
				{
				 printf("\n\t%s\t\t",ptr->dname);  
				 if(ptr->f.fcnt==0)
						printf("EMPTY");
				 else
				 {
					for(j=0;j<ptr->f.fcnt;j++)
							 printf("%s    ",ptr->f.fname[j]); 
				 } //end else
				 ptr=ptr->next; 
				}
				printf("\n");
			 	break;	 	
}
}while(ch!=6);
}
