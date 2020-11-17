#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct input
{
char **data;
int count;
}in;


float avg=0.0,median,sd;
int min,max; /* this data is shared by the thread(s) */

void *worker_avg(void *param)
{
struct input *t=(struct input *)param;
int i,sum = 0;
for (i = 0; i < t->count; i++)
  sum += atoi(t->data[i]);
avg=(float)sum/(t->count-1);
pthread_exit(0);
}

void *worker_min(void *param)
{
struct input *t=(struct input *)param;
int i;
min = atoi(t->data[1]);
for (i = 2; i < t->count; i++)
if (atoi(t->data[i])<min)
min=atoi(t->data[i]);
pthread_exit(0);
}

void *worker_max(void *param)
{
struct input *t=(struct input *)param;
int i;
max = atoi(t->data[1]);
for (i = 2; i < t->count; i++)
if (atoi(t->data[i])>max)
max=atoi(t->data[i]);
pthread_exit(0);
}

void *worker_median(void *param)
{
struct input *t=(struct input *)param;
int i,j,n=t->count;
char * temp;
for(i = 1;i < n-1;i++) //sort
{
 for(j = 1;j < n-i-1;j++) 
 {
    if(atoi(t->data[j]) > atoi(t->data[j+1]))
    {
      temp=t->data[j];
      t->data[j]=t->data[j+1];
      t->data[j+1]=temp;  
    }
  }
}

if((n-1)%2==0)
{ median=(float) ( atof(t->data[n/2]) + atof(t->data[(n+1)/2]) ) /2;  }
else
	  median=atof(t->data[n/2]);
pthread_exit(0);
}

void *worker_sd(void *param)
{
struct input *t=(struct input *)param;
int arr[t->count-1] , i;
float average,sum=0;
for(i=0;i<t->count-1;i++)
  arr[i]=atoi(t->data[i+1]); 
for (i = 0; i < t->count-1; i++)
  sum += arr[i];
average=(float)sum/(t->count-1);
sum=0;
for (i = 0; i < t->count-1; i++)
	sum+=(float)pow((arr[i]-average),2); 
sd=(float)sqrt(sum/(t->count-1));
pthread_exit(0);
}


void main(int argc, char *argv[])
{
pthread_t tid1,tid2,tid3,tid4,tid5; /* the thread identifier */
pthread_attr_t attr; /* set of thread attributes */
/* get the default attributes */
pthread_attr_init(&attr);
/* create the thread */
in.data=argv;
in.count=argc;
pthread_create(&tid1,&attr,worker_avg,&in);
pthread_create(&tid2,&attr,worker_min,&in);
pthread_create(&tid3,&attr,worker_max,&in);
pthread_create(&tid4,&attr,worker_median,&in);
pthread_create(&tid5,&attr,worker_sd,&in);

/* wait for the thread to exit */
pthread_join(tid1,NULL);
pthread_join(tid2,NULL);
pthread_join(tid3,NULL);
pthread_join(tid4,NULL);
pthread_join(tid5,NULL);

printf("Avg = %.2f\n",avg);
printf("Min = %d\n",min);
printf("Max = %d\n",max);
printf("Median = %.2f\n",median);
printf("Standard Deviation =%.2f\n",sd);
}
