#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
char pid[3];
int at;
int bt;
int et;  //et is the time at which a process begins execution  //used to store original bt in rr,priorp
int wt;
int tt;
int pr;
int finished;
}process;

typedef struct{  //used for sjf preemptive  gantt chart
	char pid[3];
	int st;
	int et;
}gantt;

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

void round_robin_gantt(process *p,int n,int tq)
{ 
 int cnt=0,t=0,flag=0,i=0,j=0,k;
 int arr[50];
 for(k=0;k<n;k++) 
    p[k].et=p[k].bt;
 sort_at(p,n);
 printf("\n\t\t");
 for(k=0;k<15*n;k++)
   printf("-");
 printf("\n\t\t|");
 while(cnt!=n)
 { 
  if(p[i].at<=t)
  { 
   if(p[i].et<=tq && p[i].et!=0)  //process not yet completed and rem bt <tq
   { 
   t+=p[i].et;
   p[i].et=0;
   arr[j]=t;  
   j++;  
   cnt++;
   p[i].wt=t-p[i].at-p[i].bt;
   p[i].tt=p[i].wt+p[i].bt;
   printf("  %s  | ",p[i].pid);
   }
   else if(p[i].et!=0) //p[i].et>tq
   {
   t+=tq;
   p[i].et-=tq;
   arr[j]=t;  
   j++;
   printf("  %s  | ",p[i].pid);
   }
   i=(i+1)%6;
  }
  else
  {
   i=0;
  }
}//end while
printf("\n\t\t");
for(k=0;k<15*n;k++)
   printf("-");
t=0;
printf("\n\t\t");
printf("%-2d  ",t); //zero
for(i=0;i<j;i++)
   printf("  %-2d    ",arr[i]);
printf("\n\t\t");
for(k=0;k<15*n;k++)
   printf("-");
printf("\n\n");
}

void rr_displayProcessDetails(process * p,int n)
{
int i,total_turn=0,total_wait=0;
float avg_wait,avg_turn;
printf("\n Process id  Arrival time  Burst time  Waiting time  Turnaround time\n");
for(i=0;i<n;i++)
{
total_turn+=p[i].tt;  
total_wait+=p[i].wt; 
printf("\n %s \t\t %d \t\t  %d \t\t %d \t\t %d \n",p[i].pid,p[i].at,p[i].bt,p[i].wt,p[i].tt);
}
avg_wait=(float)total_wait/n;
avg_turn=(float)total_turn/n;
printf("\nAvg wait time: %.1f\n",avg_wait);
printf("Avg turnaround time : %.1f\n",avg_turn);
return;
}

void main()
{
int n,i,tq,ch;
process * p;
printf("\n****Scheduling algorithms****");
printf("\n\t1.PRIORITY--NON PREMPTIVE\n\t2.PRIORITY--PREMPTIVE\n\t3.ROUND ROBIN\n");
printf("\nSelect a scheduling algorithm (1/2): ");
scanf("%d",&ch);
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
if(ch==1 || ch==2)
{
 printf("Enter the priority: ");
 scanf("%d",&p[i].pr);
}
p[i].finished=0;
}
if (ch==3)
{ printf("\nEnter the time quantum: ");
 scanf("%d",&tq);
}
switch(ch)
{
/*case 1: sort_pr(p,n);
        printf("\n\t\tGANTT CHART--PRIORITY NON PREMPTIVE\n");  
        prior_np_gantt_chart(p,n);
        displayProcessDetails(p,n);
        break;

case 2: printf("\n\t\tGANTT CHART--PRIORITY PREMPTIVE\n");
	prior_p_gantt_calc(p,n);
	break;*/

case 3: printf("\n\t\tGANTT CHART--ROUND ROBIN\n");
	round_robin_gantt(p,n,tq);
        rr_displayProcessDetails(p,n);
        break;

default: printf("\nInvalid option\n");
}
}

  
