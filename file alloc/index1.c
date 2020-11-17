#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct memory Memory;

struct memory{
  int block_id;
  char fname[50];
  int flag;
  Memory * next;
	int  *arr;
};

typedef struct {
  char fname[50];  
  int fsize;
	int index_block_id;
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
    if(head==NULL)
    	 head=temp;
    else
    {
     temp->next=head;
     head=temp;
    }
  }
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
 Memory* temp=head,* ptr;
 int i,j=0,ind;
 
 //allocates index block
 for(i = 0; i < nof; i++)
 {
  if(farr[i].fsize>no_fb)
  {
    printf("\nNot enough memory available for file %s!",farr[i].fname);
    farr[i].index_block_id=-1;//=farr[i].end_block_id;
    continue;
  }
  while(1)
  {
   ind = random()%nob; 
   if(check(ind) == 1)
   { 	
    farr[i].index_block_id=ind; 
    temp=head;
  	while(temp!=NULL && temp->block_id!=ind)
  			temp=temp->next;
  	strcpy(temp->fname,farr[i].fname);
 		temp->flag=1;
 		temp->arr=(int *)malloc(sizeof(int)*farr[i].fsize);
 		no_fb--;
    break;
   } //end if check
  }//end while
 }  //end for i
//allocates blocks and adds it to the index block array
 for(i = 0; i < nof; i++)
 {
  if(farr[i].fsize<=no_fb)
  {
   ptr=head;
 	 while(ptr->next!=NULL && ptr->block_id!=farr[i].index_block_id)
  	    ptr=ptr->next;    //ptr points to the file's index block   
   for(j=0;j<farr[i].fsize;j++)
   {
    while(1)
    {
    ind = random()%nob; 
    if(check(ind) == 1)
    	  break;
    }//end while
		temp=head; 
  	while(temp->next!=NULL && temp->block_id!=ind)
  	    temp=temp->next;  
  	    
 		strcpy(temp->fname,farr[i].fname);
 		temp->flag=1;
 		no_fb--;  
  	ptr->arr[j]=ind;
 	 } //end for j;
  }  //end if farr[i].fsize<=no_fb
 } //end for i
}

void display(File farr[],int nof)
{ int i,j;
	Memory * temp;
	printf("\nFile name\tIndex Block No\tBlocks Allocated\n");
  for(i = 0; i < nof; i++)
  {
    temp=head;
    if(farr[i].index_block_id!=-1)
    {
     printf("\n%s\t\t%d\t\t",farr[i].fname,farr[i].index_block_id);   
      while(temp!=NULL && temp->block_id!=farr[i].index_block_id)
   			temp=temp->next;
      for(j=0;j<farr[i].fsize;j++)
      		  printf("%d ",temp->arr[j]);  
    }
  }
  printf("\n");
}

int main()
{
  int nof, size;
  printf("Enter size of the main memory in KB: ");
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
    farr[i].index_block_id=-1;
   }
  allocate(farr,nof);
  display(farr,nof);
  return 0;
}
