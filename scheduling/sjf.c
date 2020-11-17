#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
char pid[2];
int at;
int bt;
int et;  //et is the time at which a process begins execution
int wt;
int tt;
int finished;
}process;

void sort_bt(process * arr,int n)
{
 int i,j;
 process key;
 for(i=1;i<n;i++)
 {
  key=arr[i];
  j=i-1;
  while((j>=0) && (arr[j].bt>key.bt))
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

void sjf_gantt_chart(process *p,int n)
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
   printf(" %s  | ",p[i].pid);
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
 printf("     | ");  //no process for execution //so idle
 t=min_at;
 arr[x]=t;  x++;
}
} //end while

printf("\n\t\t");
for(k=0;k<9*n;k++)
   printf("-");
t=0;
printf("\n\t\t");
printf("%d   ",t); //zero

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
p[i].finished=0;
}
printf("\n****Scheduling algorithms****");
printf("\n\t1.FCFS\n\t2.SJF");
printf("\nSelect a scheduling algorithm (1/2): ");
scanf("%d",&ch);
switch(ch)
{
case 2: sort_bt(p,n);
        printf("\n\t\t\tGANTT CHART");  
        sjf_gantt_chart(p,n);
        displayProcessDetails(p,n);
}
}
