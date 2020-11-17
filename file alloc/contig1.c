#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct memory Memory;

struct memory{
  int block_id;
  char fname[50];
  int flag;
  Memory * next;
};

typedef struct {
  char fname[50];  
  int fsize;
  int st_block_id;
}File;

Memory * head=NULL;
int memsize, blocksize, nob;

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

void display(File farr[],int nof)
{ int i;
  printf("\nFile\tStarting Block\tLength(no of blocks)\n");
  for(i = 0; i < nof; i++){
    if(farr[i].st_block_id!=-1)
       printf("%s\t%d\t%d\n",farr[i].fname,farr[i].st_block_id,farr[i].fsize);
  }
}

int checkfree(int size)
{
 int i=0,j,cnt=0;
 Memory* temp=head;
 Memory * ptr;
 while(temp!=NULL)
 {
  if(temp->flag == 0)
  {
   ptr=temp;
   cnt=0;
   while(ptr!=NULL && ptr->flag == 0)
   { 
   		cnt++;
			if(cnt == size)
	  			return 1;  //available
			ptr=ptr->next;
   }
   temp=ptr->next;
  } //end if 
  else 
    temp=temp->next;
 } //end while temp
 return 0;  //not available
}

int check(int ind, int size)
{
  int cnt=0;
  Memory* temp=head;
  while(temp!=NULL && temp->block_id!=ind)
  	temp=temp->next;
  while(temp!=NULL && temp->flag == 0)
  { 
 		cnt++;
		if(cnt == size)
	 			return 1;  //available
		temp=temp->next;
  }
  return 0;  //not available
}

void allocate(File farr[],int nof)
{
 Memory* temp=head;
 int i,j=0,ind;
 for(i = 0; i < nof; i++)
 {
  if(checkfree(farr[i].fsize) == 1)
  {
   while(1)
   {
    ind = random()%nob; 
    if(check(ind,farr[i].fsize) == 1)
    {
     farr[i].st_block_id=ind;
     temp=head; 
  	 while(temp!=NULL && temp->block_id!=ind)
  	    temp=temp->next;  
  	 j=0;
		 do{
			 temp->flag=1;
			 strcpy(temp->fname,farr[i].fname);
			 temp=temp->next;
		   j++;
			}while(j != farr[i].fsize);
		 break;
    } //end if check
   }  //end while
  }   //end if check free
  else
  {
    printf("\nNot enough memory available for file %s!",farr[i].fname);
    farr[i].st_block_id=-1;
  } //end else
 }
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
  printf("\nEnter the no. of files: ");
  scanf("%d", &nof);
  File farr[nof];
  for(int i = 0; i < nof; i++)
  {
    printf("Enter the file name: ");
    scanf("%s",farr[i].fname);
    printf("Enter the size of the file: ");
    scanf("%d",&size);
    farr[i].fsize=size/blocksize;
    if(size%blocksize!=0)
    	farr[i].fsize++;
  }
  allocate(farr,nof);
  display(farr,nof);
  return 0;
}
