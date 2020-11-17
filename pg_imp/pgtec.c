#include<stdio.h>
#include<stdlib.h>

typedef struct PageTable pagetable;

int pgsize, phy_size;
int no_of_frames, noff;  //noff-no of free frames
int frames[100];

struct PageTable
{
  int pgno;
  int fr_no;
  pagetable* next;
};

pagetable* process[10];

void display_table(pagetable *head)
{
  for(pagetable *temp = head; temp != NULL; temp = temp->next)
    printf("Page %d: Frame %d\n", temp->pgno, temp->fr_no);
  printf("\n");
}

void allocate()
{
  int i,pid, mem_req, no_of_pages,fr_idx=0;
  pagetable *head, *temp, *prev;
  printf("\nEnter the process ID: ");
  scanf("%d", &pid);
  printf("Enter the memory required for the process in KB: ");
  scanf("%d", &mem_req);
  no_of_pages = mem_req/pgsize;
  if(mem_req%pgsize!=0)
    no_of_pages++; 
  printf("\nProcess is divided into %d pages.\n", no_of_pages);
  if(no_of_pages>noff)
  {
    printf("Not available!\n");
    return;
  }
  for(i=0;i<no_of_pages;i++)
  {
    temp = (pagetable*)malloc(sizeof(pagetable));		
    temp->pgno = i;
    while(frames[fr_idx]==0)  fr_idx++;  //frame not free
    temp->fr_no = fr_idx;
    frames[fr_idx]=0;  //frame occupied
    fr_idx++;
    temp->next = NULL;
    noff--;
    if(i==0)
      head = temp;
    else
      prev->next = temp;
    prev = temp;
  }
  process[pid] = head;
  printf("Page Table for process ID: %d\n", pid);
  display_table(process[pid]);
}

void deallocate()
{
  pagetable *pd, *temp, *d;
  int pid;
  printf("Enter the process id to deallocate:");
  scanf("%d", &pid);
  temp = process[pid];
  if(temp==NULL)
  {
    printf("Not allocated!\n");
    return;
  }
  while(temp!=NULL)
  {
    d = temp;
 		frames[d->fr_no]=1;  //frame is made free
		noff++;
    temp = temp->next;
    free(d);
  }
  process[pid] = NULL;
  printf("Deallocated!\n");
}

void display_all()
{
int i;
  for(i = 0; i < 10; i++)
    if(process[i] != NULL)
    { printf("Page Table for process ID: %d\n", i);
      display_table(process[i]);
    }
}

void display_free_frames()
{
int i;
  for(i=0;i<no_of_frames;i++)
    if(frames[i]==1)  printf("%d ", i);
  printf("\n");
}

void addressmap()
{
  int i,pid, la, page_no,offset,frame_no, pa;
  pagetable *h , *temp;
  printf("Enter the process id: ");
  scanf("%d", &pid);
  printf("Enter the logical address: ");
  scanf("%d", &la);
  page_no = la / (pgsize * 1024);
  offset = la % (pgsize * 1024);
  temp=process[pid];
  for(i = 0; i < page_no; i++)  //find the page
    temp = temp->next;
  frame_no = temp->fr_no;
  pa = (frame_no * pgsize * 1024 )+ offset;  //frame size=page size
  printf("Physical address: %d\n", pa);
}

void main()
{
  int i,fr,ch=0;
  for(i=0;i<100;i++)  frames[i]=0;  //frame free
  printf("\n\tPAGING TECHNIQUE");
  printf("\n\nEnter physical memory size in KB: ");
  scanf("%d", &phy_size);
  printf("Enter the page size in KB: ");
  scanf("%d", &pgsize);
  no_of_frames = phy_size / pgsize;        //page size =frame size
  printf("Physical memory is divided into %d frames.\n", no_of_frames);
  for(i = 0; i < no_of_frames/2; i++)    //half of the frames are free
  {
  	fr = random()%no_of_frames;		
    if(frames[fr] != 1)  
    {
      frames[fr] = 1;
      noff++;
    }
    else   //if same no is being generated again
       i--;
  }
  do
  {
    printf("\n1.Process Request\n2.Deallocate\n3.Page Table display for all input process\n4.Free Frame list display\n5.Address Mapping\n6.Exit\n\nEnter your choice: ");
    scanf("%d", &ch);
    switch(ch)
    {
    case 1:
      allocate();  break;
    case 2:
      deallocate(); break;
    case 3:
      display_all(); break;
    case 4:
      display_free_frames(); break;
    case 5:
      addressmap(); break;
    case 6:
      exit(0);
    }
  }while(1);
}
