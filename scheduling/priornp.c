#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
char pid[3];
int at;
int bt;
int et;  //et is the time at which a process begins execution  //used to store original bt in sjfp
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


void sort_pr(process * arr,int n)
{
 int i,j;
 process key;
 for(i=1;i<n;i++)
 {
  key=arr[i];
  j=i-1;
  while((j>=0) && (arr[j].pr>key.pr))
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
printf("\n Process id  Arrival time  Burst time  Priority  Waiting time  Turnaround time\n");
for(i=0;i<n;i++)
{
p[i].wt=p[i].et-p[i].at;  
p[i].tt=p[i].wt+p[i].bt; 
total_turn+=p[i].tt;  
total_wait+=p[i].wt; 
printf("\n %s \t\t %d \t\t %d \t %d \t\t %d \t\t %d  \n",p[i].pid,p[i].at,p[i].bt,p[i].pr,p[i].wt,p[i].tt);
}
avg_wait=(float)total_wait/n;
avg_turn=(float)total_turn/n;
printf("\nAvg wait time: %.1f\n",avg_wait);
printf("Avg turnaround time : %.1f\n",avg_turn);
return;
}

int find_min_at(process* p,int n)
{
int i,j,min;
for(j=0;j<n;j++)
{
  if(p[j].finished==0)
  {  min=p[j].at;
     for(i=j+1;i<n;i++)
       if(p[i].finished==0 && p[i].at<min)
          min=p[i].at;
     return min;
  }
}
}

void prior_np_gantt_chart(process *p,int n)
{
int i=0,cnt=0,t=0,x=0; //t keeps a track of current time
int k,y,min_at;
int arr[n]; //for holding the gantt chart values
printf("\n\t\t");
for(k=0;k<9*n;k++)
   printf("-");
printf("\n\t\t|");

while(cnt!=n)  //cnt keeps a cnt of the no of processes completed   
{
min_at=find_min_at(p,n);
if(min_at<=t)
{ 
  if(t>=p[i].at && p[i].finished==0)  //process has arrived and not executed
  {
   printf("  %s  | ",p[i].pid);
   p[i].et=t;  
   t+=p[i].bt;    //update current time
   arr[x]=t;  x++;
   p[i].finished=1;
   cnt++;         //increment count
   i=0;   //everytime it would check from the begining of the array
  }
  else 
    i=(i+1)%n;
}
else  //min_at>=t
{
 printf("      |");  //no process for execution //so idle
 t=min_at;
 arr[x]=t;  x++;
}
} //end while

printf("\n\t\t");
for(k=0;k<9*n;k++)
   printf("-");
t=0;
printf("\n\t\t");
printf("%-2d   ",t); //zero

for(y=0;y<x;y++)
   printf(" %-2d     ",arr[y]); 
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
printf("\n****Scheduling algorithms****");
printf("\n\t1.PRIORITY--NON PREMPTIVE\n\t2.PRIORITY--PREMPTIVE\n");
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
printf("Enter the priority: ");
scanf("%d",&p[i].pr);
p[i].finished=0;
}
switch(ch)
{
case 1: sort_pr(p,n);
        printf("\n\t\tGANTT CHART--PRIORITY NON PREMPTIVE\n");  
        prior_np_gantt_chart(p,n);
        displayProcessDetails(p,n);
        break;

case 2:/* printf("\n\t\tGANTT CHART--PRIORITY PREMPTIVE\n");
	sjf_p_gantt_calc(p,n);
	break;*/

default: printf("\nInvalid option\n");
}
}
