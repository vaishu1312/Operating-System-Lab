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

void displayProcessDetails(process * p,int n)
{
int i,total_turn=0,total_wait=0;
float avg_wait,avg_turn;
printf("\n Process id  Arrival time  Burst time  Waiting time  Turnaround time\n");
for(i=0;i<n;i++)
{
p[i].wt=p[i].et-p[i].at;  
p[i].tt=p[i].wt+p[i].bt; 
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

void sjf_p_displayProcessDetails(process * p,int n,int idx_g,gantt g[])
{
int total_turn=0,total_wait=0;
float avg_wait,avg_turn;
printf("\n Process id  Arrival time  Burst time  Waiting time  Turnaround time\n");

for(int i=0;i<n;i++)
{
 int prev_et=0;
 p[i].wt=0;
 for(int j=0;j<idx_g;j++)
 {
   if(strcmp(p[i].pid,g[j].pid)==0)
   {
   p[i].wt+=(g[j].st-prev_et);
   prev_et=g[j].et;
   }
 }
 p[i].wt-=p[i].at;
 p[i].tt=p[i].wt+p[i].bt;

total_turn+=p[i].tt;  
total_wait+=p[i].wt; 
printf("\n %s \t\t %d \t\t  %d \t\t %d \t\t %d \n",p[i].pid,p[i].at,p[i].bt,p[i].wt,p[i].tt);
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
  if (t<p[i].at)   {   printf("      |");    t=p[i].at;        arr[x]=t;  x++;  }  //check if the process has arrived
  else             {  p[i].et=t;  printf("  %s  | ",p[i].pid); t+=p[i].bt; i++; arr[x]=t; x++;}  //et is the time at which the process has started to execute
}
printf("\n\t\t");
for(k=0;k<9*n;k++)
   printf("-");
printf("\n\t\t");
t=0; 
printf("%-2d   ",t); //zero
for(y=0;y<x;y++)
   printf(" %-2d     ",arr[y]); 
printf("\n\t\t");

for(k=0;k<9*n;k++)
   printf("-");
printf("\n\t\t");
printf("\n\n");
}

void sjf_np_gantt_chart(process *p,int n)
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

void sjf_p_gantt_chart(gantt g[],int idx_g,int n)
{
 int k,i,t;
 printf("\n\t\t");
 for(k=0;k<8*idx_g;k++)
   printf("-");
 printf("\n\t\t|");
 for(i=0;i<idx_g;i++)
 {
  if(i!=0 && g[i].st==g[i-1].et)
       printf("  %s  | ",g[i].pid);
  else if(i!=0)
        printf("       |   %s  | ",g[i].pid);
  else
       printf("  %s  | ",g[i].pid);
 }
 printf("\n\t\t");
 for(k=0;k<8*idx_g;k++)
   printf("-");
 t=0;
 printf("\n\t\t");
 printf("%-2d  ",t); //zero

 for(i=0; i<idx_g;i++)
 {
  if(i!=0 && g[i].st==g[i-1].et)
        printf("  %-2d    ",g[i].et);
  else if(i!=0)
        printf("  %-2d      %-2d    ",g[i].st,g[i].et);
  else
        printf("  %-2d    ",g[i].et);
 }
printf("\n\t\t");
for(k=0;k<8*idx_g;k++)
   printf("-");
printf("\n\t\t");
printf("\n\n");
}


int find_midx_et(process* p,int n,int current_t) //find idx of proc with min rem burst time among processes that have arrived and not finished completely
{
int i,j,min,midx=-1;
for(j=0;j<n;j++)
{
  if(p[j].finished==0 && p[j].at<=current_t)
  {  min=p[j].et;  midx=j;//remaining burst time
     for(i=j+1;i<n;i++)
       if(p[i].finished==0 && p[i].at<=current_t && p[i].et<min)
         { min=p[i].et;  midx=i;  }
     return midx;
  }
}
}

void sjf_p_gantt_calc(process *p,int n)
{
gantt g[50];
int idx_g=0,cnt=0,t=0; //cnt no of processes finished //t current time
int midx,k,cjob=-1;
for(k=0;k<n;k++)
  p[k].et=p[k].bt; //et in p is rem btsjfp_gantt_chart(gantt g[],int idx_g)
while(cnt!=n)
{ 
midx=find_midx_et(p,n,t);
if(midx!=-1)  //if there is a min job at this time
{ 
 if(midx!=cjob)  //if the mi job is not the current job
 { cjob=midx;
   strcpy(g[idx_g].pid,p[midx].pid);
   g[idx_g].st=t; 
   p[midx].et-=1; //reduce rem burst time of that process by 1    
   t++; 		//increment current time 
   g[idx_g].et=t; //et in g is end time                   
   if(p[midx].et==0)
   {   p[midx].finished=1;   cnt++;  }
   idx_g++;   
 }
 else //if cjob=minidx //minidx is the current job
 {  
  idx_g--;
  p[midx].et-=1; //reduce rem burst time of that process by 1    
  t++;
  g[idx_g].et=t;
  if(p[midx].et==0)
  {   p[midx].finished=1;   cnt++;  }
  idx_g++;   
 } 
} // end midx!=-1
else  //wait till a process arrives
 t++;    
}//end while
//for(int m=0;m<idx_g;m++)
 //printf("\n%s\t%d\t%d",g[m].pid,g[m].st,g[m].et);
sjf_p_gantt_chart(g,idx_g,n);
sjf_p_displayProcessDetails(p,n,idx_g,g);
}

void main()
{
int n,i,ch;
process * p;
printf("\n****Scheduling algorithms****");
printf("\n\t1.FCFS\n\t2.SJF--NON PREMPTIVE\n\t3.SJF--PREMPTIVE\n");
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
p[i].finished=0;
}
switch(ch)
{
case 1: sort_at(p,n);
        printf("\n\t\tGANTT CHART--FCFS");  
        fcfs_gantt_chart(p,n);
        displayProcessDetails(p,n);
        break;

case 2: sort_bt(p,n);
        printf("\n\t\tGANTT CHART--SJF NON PREMPTIVE\n");  
        sjf_np_gantt_chart(p,n);
        displayProcessDetails(p,n);
        break;

case 3: printf("\n\t\tGANTT CHART--SJF PREMPTIVE\n");
	sjf_p_gantt_calc(p,n);
	break;

default: printf("\nInvalid option\n");
}
}
