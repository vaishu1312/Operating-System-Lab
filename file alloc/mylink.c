//uses ptr for start and end block

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct memory Memory;

struct memory{
  int block_id;
  char fname[50];
  int flag;
  Memory * next;
  Memory * next_fb;
};

typedef struct {
  char fname[50];  
  int fsize;
  Memory* start;
  Memory* end;
}File;

Memory * head=NULL;
int memsize, blocksize, nob;
int no_fb;  //no of free blocks

void initialise()
{
  for(int i = nob-1; i >=0; i--)
  {
    Memory * temp=(Memory *)malloc(sizeof(Memory));
    temp->block_id = i;
    strcpy(temp->fname,"");
    temp->flag = 0;     //0--free  1---not free
    temp->next=NULL;
    temp->next_fb=NULL;
    if(head==NULL)
    	 head=temp;
    else
    {
     temp->next=head;
     head=temp;
    }
  }
}

void display(File farr[],int nof)
{ int i;
	Memory * temp;
	printf("\nFile name\tBlocks Allocated\n");
  for(i = 0; i < nof; i++)
  {
    temp=head;
    if(farr[i].start!=NULL)
    {
     printf("\n%s\t\t",farr[i].fname);   
     temp=farr[i].start;
  		while(temp->next_fb!=NULL)
      {  printf("%d->",temp->block_id);  temp=temp->next_fb;  } 
      printf("%d",temp->block_id);
    }
  }
  printf("\n");
}

int check(int ind)
{
  Memory* temp=head;
  while(temp!=NULL && temp->block_id!=ind)
  	temp=temp->next;
  if(temp!=NULL && temp->flag == 0)
	 			return 1;  //available
  return 0;  //not available
}

void allocate(File farr[],int nof)
{
  Memory * ptr,*temp;
  int i,j,ind;
  for(i = 0; i < nof; i++)
  {  
   if(farr[i].fsize<=no_fb)
   {  
    for(j=0;j<farr[i].fsize;j++)
    {    
    while(1)
    {
     ind = random()%nob;   
  	 if(check(ind) == 1)
    	  break;
    }  //end while  
    temp=head;
    while(temp!=NULL && temp->block_id!=ind)
          temp=temp->next; 

 		strcpy(temp->fname,farr[i].fname);
 		temp->flag=1;
 		no_fb--;
 		
    if(farr[i].start==NULL)
    		farr[i].start=temp; 
    else
        ptr->next_fb=temp;

 		ptr=temp;
    }//end for j
    farr[i].end=temp;
   } //end if
   else
   {
    farr[i].start=NULL;	 
     printf("Not enough memory available for file : %s!\n",farr[i].fname); 
   }
  } //end for
}
 
int main()
{
  int nof, size;
  printf("Enter size of memory in KB: ");
  scanf("%d", &memsize);
  printf("Enter size of block in KB: ");
  scanf("%d", &blocksize);
  nob = memsize/blocksize;
  printf("\nMain memory is split into %d blocks\n",nob);
  initialise();
  no_fb=nob;
  printf("\nEnter the no. of files: ");
  scanf("%d", &nof);
  File farr[nof];
  for(int i = 0; i < nof; i++)
  {
    printf("\nEnter the file name: ");
    scanf("%s",farr[i].fname);
    printf("Enter the size of the file: ");
    scanf("%d",&size);
    farr[i].fsize=size/blocksize;
    if(size%blocksize!=0)
    	farr[i].fsize++;
    farr[i].start=farr[i].end=NULL;
  }
  allocate(farr,nof);
  display(farr,nof);
  return 0;
}
