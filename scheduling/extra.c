#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
char pid[2];
int at;
int bt;
int et;
int wt;
int tt;
}process;

void sort_at(process * arr,int n)
{
 int i,j;
 process key;
 for(i=1;i<n;i++)
 {
  key=arr[i];
  j=i-1;
  while((j>=0) && (arr[j].at>key.at))
  {
   arr[j+1]=arr[j];
   j=j-1;
  }
 arr[j+1]=key;
 }
}

void displayProcessDetails(process * p,int n)
{
int i,total_turn=0,total_wait=0;
float avg_wait,avg_turn;
printf("\n Process id  Arrival time  Burst time  Turnaround time  Waiting time\n");
for(i=0;i<n;i++)
{
p[i].wt=p[i].et-p[i].at;  
p[i].tt=p[i].wt+p[i].bt; 
total_turn+=p[i].tt;  
total_wait+=p[i].wt; 
printf("\n %s \t\t %d \t\t  %d \t\t %d \t\t %d \n",p[i].pid,p[i].at,p[i].bt,p[i].tt,p[i].wt);
}
avg_wait=(float)total_wait/n;
avg_turn=(float)total_turn/n;
printf("\nAvg wait time: %.1f\n",avg_wait);
printf("Avg turnaround time : %.1f\n",avg_turn);
}

void fcfs_gantt_chart(process *p,int n)
{
int arr[n];
int i=0,k,j=0,t=0,x=0,y;
printf("\n\t\t");
for(k=0;k<9*n;k++)
   printf("-");
printf("\n\t\t|");
while(i<n)  //i keeps a cnt of the no of processes completed   //t is the current time
{
  if (t<p[i].at)   {  printf("     | ");    t=p[i].at;        arr[x]=t;  x++;  }  //check if the process has arrived
  else             {  p[i].et=t;  printf(" %s  | ",p[i].pid);   t+=p[i].bt; i++; arr[x]=t; x++;}  //et is the time at which the process has started to execute
}
printf("\n\t\t");
for(k=0;k<9*n;k++)
   printf("-");
printf("\n\t\t");
t=0; printf("%d   ",t);
for(y=0;y<x;y++)
   printf(" %d     ",arr[y]); 
printf("\n\t\t");
for(k=0;k<9*n;k++)
   printf("-");
printf("\n\t\t");
printf("\n\n");
}


void main()
{
int n,i,ch;
process * p;
printf("\nEnter the no of processes: ");
scanf("%d",&n);
p=malloc(sizeof(process)*n);
for(i=0;i<n;i++)
{
printf("\nEnter the pid: ");
scanf("%s",p[i].pid);
printf("Enter the arrival time: ");
scanf("%d",&p[i].at);
printf("Enter the burst time: ");
scanf("%d",&p[i].bt);
}
printf("\n****Scheduling algorithms****");
printf("\n\t1.FCFS\n\t2.SJF");
printf("\nSelect a scheduling algorithm (1/2): ");
scanf("%d",&ch);
switch(ch)
{
case 1: sort_at(p,n);
        printf("\n\t\t\tGANTT CHART");  
	fcfs_gantt_chart(p,n);
        displayProcessDetails(p,n);
}
}

