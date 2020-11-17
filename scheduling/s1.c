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

typedef struct{
	char pid[3];
	int st;
	int et;
}gantt;

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

void sjf_p_gantt_chart(gantt g[],int idx_g,int n)
{
 int k,i,t;
 printf("\n\t\t");
 for(k=0;k<9*n;k++)
   printf("-");
 printf("\n\t\t|");
 for(i=0;i<idx_g;i++)
 {
  if(i!=0 && g[i].st==g[i-1].et)
       printf("  %s | ",g[i].pid);
  else if(i!=0)
        printf("      |   %s | ",g[i].pid);
  else
       printf("  %s | ",g[i].pid);
 }
 printf("\n\t\t");
 for(k=0;k<9*n;k++)
   printf("-");
 t=0;
 printf("\n\t\t");
 printf("%-2d   ",t); //zero

 for(i=0; i<idx_g;i++)
 {
  if(i!=0 && g[i].st==g[i-1].et)
        printf(" %-2d    ",g[i].et);
  else if(i!=0)
        printf(" %-2d     %-2d    ",g[i].st,g[i].et);
  else
        printf(" %-2d    ",g[i].et);
 }
printf("\n\t\t");
for(k=0;k<9*n;k++)
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
printf("\n\t1.FCFS\n\t2.SJF");
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
/*case 1: sort_at(p,n);
        printf("\n\t\t\tGANTT CHART");  
        fcfs_gantt_chart(p,n);
        displayProcessDetails(p,n);
        break;*/

case 2: /*sort_bt(p,n);
        printf("\n\t\t\tGANTT CHART");  
	printf("\nSJF NON PREMPTIVE");
        sjf_gantt_chart(p,n);
        displayProcessDetails(p,n);*/
        printf("\n\t\t\tGANTT CHART");  
	printf("\nSJF PREMPTIVE");
	sjf_p_gantt_calc(p,n);
	break;

default: printf("\nInvalid option\n");
}
}
