#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
char pid[3];
int at;
int bt;
int et;  //et is the time at which a process begins execution  //used to store original bt in priority premptive
int wt;
int tt;
int pr;
int finished;
}process;

typedef struct{  //used for priority preemptive  gantt chart
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

void prior_p_displayProcessDetails(process * p,int n,int idx_g,gantt g[])
{
int total_turn=0,total_wait=0;
float avg_wait,avg_turn;
printf("\n Process id  Arrival time  Burst time  Priority  Waiting time  Turnaround time\n");

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
printf("\n %s \t\t %d \t\t %d \t %d \t\t %d \t\t %d  \n",p[i].pid,p[i].at,p[i].bt,p[i].pr,p[i].wt,p[i].tt);
}
avg_wait=(float)total_wait/n;
avg_turn=(float)total_turn/n;
printf("\nAvg wait time: %.1f\n",avg_wait);
printf("Avg turnaround time : %.1f\n",avg_turn);
}

void prior_p_gantt_chart(gantt g[],int idx_g,int n)
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
printf("\n\n");
}


int find_high_pr_idx(process* p,int n,int current_t) //find idx of proc with high priority among processes that have arrived and not finished completely
{
int i,j,max,hi_pr_idx=-1;
for(j=0;j<n;j++)
{
  if(p[j].finished==0 && p[j].at<=current_t)
  {  max=p[j].pr;  hi_pr_idx=j;//remaining burst time
     for(i=j+1;i<n;i++)
       if(p[i].finished==0 && p[i].at<=current_t && p[i].pr<max)
         { max=p[i].pr;  hi_pr_idx=i;  }
     return hi_pr_idx;
  }
}
}

void prior_p_gantt_calc(process *p,int n)
{
gantt g[50];
int idx_g=0,cnt=0,t=0; //cnt no of processes finished //t current time
int hi_pr_idx,k,cjob=-1;
for(k=0;k<n;k++)
  p[k].et=p[k].bt; //et in p is rem bt
while(cnt!=n)
{ 
hi_pr_idx=find_high_pr_idx(p,n,t);
if(hi_pr_idx!=-1)  //if there is a high priority job at this time
{ 
 if(hi_pr_idx!=cjob)  //if the high priority job is not the current job
 { cjob=hi_pr_idx;
   strcpy(g[idx_g].pid,p[hi_pr_idx].pid);
   g[idx_g].st=t; 
   p[hi_pr_idx].et-=1; //reduce rem burst time of that process by 1    
   t++; 		//increment current time 
   g[idx_g].et=t; //et in g is end time                   
   if(p[hi_pr_idx].et==0)
   {   p[hi_pr_idx].finished=1;   cnt++;  }
   idx_g++;   
 }
 else //if cjob=hi_pr_idx //hi_pr_idx is the current job
 {  
  idx_g--;
  p[hi_pr_idx].et-=1; //reduce rem burst time of that process by 1    
  t++;
  g[idx_g].et=t;
  if(p[hi_pr_idx].et==0)
  {   p[hi_pr_idx].finished=1;   cnt++;  }
  idx_g++;   
 } 
} // end hi_pr_idx!=-1
else  //wait till a process arrives
 t++;    
}//end while
//for(int m=0;m<idx_g;m++)
 //printf("\n%s\t%d\t%d",g[m].pid,g[m].st,g[m].et);
prior_p_gantt_chart(g,idx_g,n);
prior_p_displayProcessDetails(p,n,idx_g,g);
}

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

