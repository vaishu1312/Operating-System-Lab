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
int pr;  //to denote priority
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
sjf_p_gantt_chart(g,idx_g,n);
sjf_p_displayProcessDetails(p,n,idx_g,g);
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
case 1:/* sort_pr(p,n);
        printf("\n\t\tGANTT CHART--PRIORITY NON PREMPTIVE\n");  
        sjf_np_gantt_chart(p,n);
        displayProcessDetails(p,n);
        break;*/

case 2: printf("\n\t\tGANTT CHART--PRIORITY PREMPTIVE\n");
	prior_p_gantt_calc(p,n);
	break;

default: printf("\nInvalid option\n");
}
}
