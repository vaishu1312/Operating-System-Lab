#include<stdio.h>
#include<stdlib.h>

int find(int ref_string, int *frames, int frames_req)
{
    for(int i=0;i<frames_req;i++)
    {
        if(ref_string==frames[i])
            return 1;
    }
    return 0;
}

int find_not_recently_used(int *ref_string, int n,int *frames, int frames_req, int curr)
{
    int cnt[frames_req],max,i;
    for(i=0;i<frames_req;i++)
    {
        cnt[i]=0;
        for(int j=curr-1;j>=0;--j)
        {
            if(frames[i]==ref_string[j])
                break;
            ++cnt[i];
        }
    }
    max=cnt[0];
    curr=0;
    i=1;
    while(i!=frames_req)
    {
        if(cnt[i]>max)
        {
            max=cnt[i];
            curr=i;
        }
        ++i;
    }
    return curr;
}
int find_not_req_next(int *ref_string, int n,int *frames, int frames_req, int curr)
{
    int cnt[frames_req],max,i;
    for(i=0;i<frames_req;i++)
    {
        cnt[i]=0;
        for(int j=curr+1;j<n;j++)
        {
            if(frames[i]==ref_string[j])
                break;
            ++cnt[i];
        }
    }
    max=cnt[0];
    curr=0;
    i=1;
    while(i!=frames_req)
    {
        if(cnt[i]>max)
        {
            max=cnt[i];
            curr=i;
        }
        ++i;
    }
    return curr;
}
void FIFO(int frames_req, int *ref_string, int n)
{
    printf("\n\n\tFIFO ALGORITHM\n\n");
    int ptr=-1, pg_fault=0,cnt,i;
    int frames[frames_req];
    for(cnt=0;cnt<frames_req;cnt++)
    {
        frames[cnt]=ref_string[cnt];
        ++pg_fault;
        printf("Page fault in inserting page %d - ",ref_string[cnt]);
        for(int j=0;j<frames_req;j++)
            if(j>cnt)
                printf("X ");
            else
                printf("%d ",frames[j]);
        printf("\n");
    }
    while(cnt!=n)
    {
        i=find(ref_string[cnt], frames,frames_req);
        if(i==0)//not available
        {
            ++pg_fault;
            if(ptr+1!=frames_req)
                ++ptr;
            else
                ptr=0;
            frames[ptr]=ref_string[cnt];
            printf("Page fault in inserting page %d - ",ref_string[cnt]);
            for(int j=0;j<frames_req;j++)
                printf("%d ",frames[j]);
            printf("\n");
        }
        ++cnt;
    }
    printf("\nTotal no of page faults = %d\n",pg_fault);
}
void optimal(int frames_req, int *ref_string, int n)
{
    printf("\n\n\tOPTIMAL ALGORITHM\n\n");
    int ptr=0, pg_fault=0,cnt,i;
    int frames[frames_req];
    for(cnt=0;cnt<frames_req;cnt++)
    {
        frames[cnt]=ref_string[cnt];
        ++pg_fault;
        printf("Page fault in inserting page %d - ",ref_string[cnt]);
        for(int j=0;j<frames_req;j++)
            if(j>cnt)
                printf("X ");
            else
                printf("%d ",frames[j]);
        printf("\n");
    }
    while(cnt!=n)
    {
        i=find(ref_string[cnt], frames,frames_req);
        if(i==0)//not available
        {
            ++pg_fault;
            ptr=find_not_req_next(ref_string,n,frames,frames_req,cnt);
            frames[ptr]=ref_string[cnt];
            printf("Page fault in inserting page %d - ",ref_string[cnt]);
            for(int j=0;j<frames_req;j++)
                printf("%d ",frames[j]);
            printf("\n");
        }
        ++cnt;
    }
    printf("\nTotal no of page faults = %d\n",pg_fault);
}

void LRU(int frames_req, int *ref_string, int n)
{
    printf("\n\n\tLEAST RECENTLY USED ALGORITHM\n\n");
    int ptr=0, pg_fault=0,cnt,i;
    int frames[frames_req];
    for(cnt=0;cnt<frames_req;cnt++)
    {
        frames[cnt]=ref_string[cnt];
        ++pg_fault;
        printf("Page fault in inserting page %d - ",ref_string[cnt]);
        for(int j=0;j<frames_req;j++)
            if(j>cnt)
                printf("X ");
            else
                printf("%d ",frames[j]);
        printf("\n");
    }
    while(cnt!=n)
    {
        i=find(ref_string[cnt], frames,frames_req);
        if(i==0)//not available
        {
            ++pg_fault;
            ptr=find_not_recently_used(ref_string,n,frames,frames_req,cnt);
            frames[ptr]=ref_string[cnt];
            printf("Page fault in inserting page %d - ",ref_string[cnt]);
            for(int j=0;j<frames_req;j++)
                printf("%d ",frames[j]);
            printf("\n");
        }
        ++cnt;
    }
    printf("\nTotal no of page faults = %d\n",pg_fault);
}

void main()
{
	int i,ref_cnt=-1,noff, frames, ref_string[20], n=0,choice;
	printf("************ PAGE REPLACEMENT *************");
	do
	{
	printf("\n\n\tMENU:\n1.Read Input\n2.FIFO\n3.Optimal\n4.LRU\n5.Exit\nEnter choice: ");
	scanf("%d",&choice);
 	switch(choice)
	{
	case 1:
               printf("Enter the number of free frames: ");
               scanf("%d",&noff);
	       printf("Enter the number of frames required by the process: ");
               scanf("%d",&frames);
               if(noff<frames)
               {
                printf("No of frames required is greater than free frames available!");
                exit(1);
              }
	      printf("Enter the reference string:\n");
	      do
	      {
		scanf("%d",&ref_string[++ref_cnt]); 
	      }while(ref_string[ref_cnt]!=-1);
	      break;

	case 2:	FIFO(frames,ref_string,ref_cnt); 	  break;
	case 3: optimal(frames,ref_string,ref_cnt);   break;
	case 4: LRU(frames,ref_string,ref_cnt);       break;
	case 5:	break;
	default: printf("\nInvalid choice ");
	}
	}while(choice!=5);

}
