#include<stdio.h>

int safety(int p,int r,int finish[],int available[],int allocation[][r],int request[][r])
{
int j,k,flag,cnt=0;

while(cnt!=p)
{ 
 flag=0;
 for(k=0;k<p;k++)
 { 
  if (finish[k]==0)
  {
   for(j=0;j<r;j++)
     if(request[k][j]>available[j])
       break;
   if(j==r)
   {  
    for(j=0;j<r;j++)
      available[j]+=allocation[k][j]; 
   finish[k]=1;
   cnt++;  
   flag=1;  //there exists a process that can be satisfied
   }
  } //end if finish
 }//end for
 if(flag==0)
  	return flag;
} //end while
return flag;
}

void main()
{
int p,r,safe,i,j,k;
printf("\t\tDEADLOCK DETECTION \n");
printf("\nEnter the no.of processes: ");
scanf("%d",&p);
printf("\nEnter the no.of resources: ");
scanf("%d",&r);

int available[r],request[p][r],allocation[p][r],finish[p];

for(k=0;k<p;k++)
  finish[k]=0;
 
printf("\nEnter the currently available no.of instances for each resource: \n");
for(i=0;i<r;i++)
{
printf("Resource %c: ",i+65);
scanf("%d",&available[i]);
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
printf("\nEnter the request for each process: ");
for(i=0;i<p;i++)
{
	printf("\nFor P%d: \n",i+1);
	for(j=0;j<r;j++)
	{
		printf("Resource %c: ",j+65);
		scanf("%d",&request[i][j]);
	}
}

safe=safety(p,r,finish,available,allocation,request);

if(safe==0)
{
printf("\nSystem is in deadlocked state");
printf("\nProcesses involved in deadlock are: ");
for(k=0;k<p;k++)
 if(finish[k]==0)
    printf("P%d ",k);
printf("\n");
}
else
	printf("\nNo deadlock\n");
}

