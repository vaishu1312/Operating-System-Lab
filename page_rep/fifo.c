#include<stdio.h>
#include<stdlib.h>

int main()
{
int i, j, k, pf=0, count=0;
int no_ff,nof, ref_str[20],ref_cnt=-1;
printf("Enter the number of free frames: ");
scanf("%d",&no_ff);
printf("Enter the number of frames required by the process: ");
scanf("%d",&nof);
int frames[nof];
for(i=0;i<nof;i++)
	frames[i]=-1;

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
	for(k=0;k<nof;k++)
		if(frames[k]==ref_str[i]) //if that page is found
			break;
			
	if(k==nof) //not found
	{
	frames[count++]=ref_str[i];
	pf++;
	printf("Page fault in inserting page %d - ",ref_str[i]);
	for(j=0;j<nof;j++)
	{
	 if(frames[j]==-1)
       printf("X ");
   else
	 		printf("%d ",frames[j]);
	}
	printf("\n");
	}
	if(count==nof)
		count=0;
}
printf("\nThe number of page faults using FIFO are %d\n",pf);
return 0;
}
