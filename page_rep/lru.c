#include<stdio.h>
#include<stdlib.h>

void display(int frames[],int nof)
{
	   for(int x=0;x<nof;x++)
		 {
		 if(frames[x]==-1)
		     printf("X ");
		 else
		 		printf("%d ",frames[x]);
		 }
		 printf("\n"); 
}

void changeRank(int rank[],int pos,int nof,int frames[])
{
	rank[pos]=nof;
	for(int k=0;k<nof;k++)
	  if(frames[k]!=-1 && k!=pos && rank[k]!=1)
	  		rank[k]--; 		 
}

int main()
{
int no_ff,nof, ref_str[20],ref_cnt=-1;
int i,pos, pf=0;

printf("Enter the number of free frames: ");
scanf("%d",&no_ff);
printf("Enter the number of frames required by the process: ");
scanf("%d",&nof);
int frames[nof];
int rank[nof];  //
for(i=0;i<nof;i++)
{	frames[i]=-1;  rank[i]=-1;  }

if(no_ff<nof)
{
 printf("No of frames required is greater than free frames available!");
 exit(1);
}

printf("\nEnter the reference string : ");
do
{
 scanf("%d",&ref_str[++ref_cnt]); 
}while(ref_str[ref_cnt]!=-1);
printf("\n");

for(i=0;i<ref_cnt;i++)
{

 for(pos=0;pos<nof;pos++)
 {
 	if(frames[pos]==ref_str[i]) //if that page is found
	{	
	 changeRank(rank,pos,nof,frames);	 		
	 break;
	}
 }  //end for pos
 		
 if(pos==nof)        //if page not found
 {
 	for(pos=0;pos<nof;pos++)
		  if(rank[pos]==1)  //pos is the position at which the new reference should be inserted in the frames arr when all frames are full
		    break;
  if(pos==nof)  //if there are empty frames  //when all frames are not full
	  for(pos=0;pos<nof;pos++)
	     if(frames[pos]==-1)
	        break;

	frames[pos]=ref_str[i];
	pf++;
	printf("Page fault in inserting page %d - ",ref_str[i]); 
	display(frames,nof);
	changeRank(rank,pos,nof,frames);	 
 }//if(pos==nof)  //if page not found
}//end for ref_str
	
printf("\nThe number of page faults using lru are %d\n",pf);
return 0;
}
