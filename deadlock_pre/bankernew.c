#include<stdio.h>

void safety(int p,int r,int available[],int allocation[][r],int need[][r])
{
int j,k,flag,cnt=0,si=0;
int finish[p],safe_seq[p];

for(k=0;k<p;k++)
  finish[k]=0;
  
while(cnt!=p)
{ 
 flag=0;
 for(k=0;k<p;k++)
 { 
  if (finish[k]==0)
  {
   for(j=0;j<r;j++)
     if(need[k][j]>available[j])
       break;
   if(j==r)
   {  
    for(j=0;j<r;j++)
      available[j]+=allocation[k][j]; 
   finish[k]=1;
   safe_seq[si]=k; si++;  
   cnt++; 
   flag=1;  //there exists a process that can be satisfied
   }
  } //end if finish
 }//end for
 if(flag==0)
 {
 		printf("\nSafety sequence not possible\n");
 		break;
 }
} //end while

if(flag==1)
{
printf("\nSafety Sequence: ");
for(k=0;k<si;k++)
printf("P%d ",safe_seq[k]);
printf("\n");
}
}

void main()
{
int p,r,flag,i,j,k;
printf("\t\tBANKER'S ALGORITHM\n");
printf("\nEnter the no.of processes: ");
scanf("%d",&p);
printf("\nEnter the no.of resources: ");
scanf("%d",&r);

int available[r],max[p][r],allocation[p][r],need[p][r];

for(k=0;k<r;k++)
  total_alloc[k]=0;
  
printf("\nEnter the currently available no.of instances for each resource: \n");
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
  
safety(p,r,available,allocation,need);
}

