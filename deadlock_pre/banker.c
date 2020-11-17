#include<stdio.h>
#include<stdlib.h>

void main()
{
int p,r,flag=0,i,j,k,cnt=0,si=0,x;
printf("\t\tBANKER'S ALGORITHM\n");
printf("\nEnter the no.of processes: ");
scanf("%d",&p);
printf("\nEnter the no.of resources: ");
scanf("%d",&r);

int available[r],max[p][r],allocation[p][r],need[p][r],finish[p],safe_seq[p],total_alloc[r];

for(k=0;k<p;k++)
  finish[k]=0;
for(k=0;k<r;k++)
  total_alloc[k]=0;
  
printf("\nEnter the available no.of instances for each resource: \n");
for(i=0;i<r;i++)
{
printf("Resource %c: ",i+65);
scanf("%d",&available[i]);
}
printf("\nEnter the maximum requirement for each process: ");
for(i=0;i<p;i++)
{
	printf("\nFor P%d: \n",i+1);
	for(j=0;j<r;j++)
	{
		printf("Resource %c: ",j+65);
		scanf("%d",&max[i][j]);
	}
}
printf("\nEnter the allocated no.of resources for each process: ");
for(i=0;i<p;i++)
{
	printf("\nFor P%d: \n",i+1);
	for(j=0;j<r;j++)
	{
		printf("Resource %c: ",j+65);
		scanf("%d",&allocation[i][j]);
		total_alloc[j]+=allocation[i][j];
	}
}
printf("\nNeed for each process\n   ");
for(k=0;k<r;k++)  printf("%c ",k+65);
printf("\n");
for(i=0;i<p;i++)
{
	printf("P%d ",i+1);
	for(j=0;j<r;j++)
	{ 
	 need[i][j]=max[i][j]-allocation[i][j]; 
	 printf("%d ",need[i][j]);
	}
	printf("\n");
}

for(j=0;j<r;j++)
  available[j]=available[j]-total_alloc[j]; 
i=0;  
while(cnt!=p)
{  
 if (finish[i]==0)
 {
  flag=0;
  for(j=0;j<r;j++)
    if(need[i][j]>available[j])
      flag=1;
  if(flag==0)
  {  
   for(j=0;j<r;j++)
     available[j]+=allocation[i][j]; 
  finish[i]=1;
  safe_seq[si]=i; si++;  
  cnt++; 
  }
 } //end if finish
 i=(i+1)%p;
} //end while

printf("\n\nSafe Sequence: ");
for(k=0;k<si;k++)
printf("P%d ",safe_seq[k]);
printf("\n");
}
