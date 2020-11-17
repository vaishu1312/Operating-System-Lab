#include <pthread.h>
#include <stdio.h>
#include<stdlib.h>

int sum, max; /* this data is shared by the thread(s) */
void *worker_sum(void *p); /* threads call this function */
void *worker_max(void *p);

struct input
{
char **data;
int count;
}in;

int main(int argc, char *argv[])
{
pthread_t tid,tid1,tid2; /* the thread identifier */
pthread_attr_t attr; /* set of thread attributes */
/* get the default attributes */
pthread_attr_init(&attr);
/* create the thread */
in.data=argv;
in.count=argc;

pthread_create(&tid,&attr,worker_sum,&in);
pthread_create(&tid1,&attr,worker_max,&in);
/* wait for the thread to exit */
pthread_join(tid,NULL);
pthread_join(tid1,NULL);
printf("sum = %d\n",sum);
printf("max = %d\n",max);
}
/* The thread will begin control in this function */

void *worker_sum(void *param)
{
struct input *t=(struct input *)param;
int i;
sum = 0;
for (i = 0; i < t->count; i++)
sum += atoi(t->data[i]);
pthread_exit(0);
}

void *worker_max(void *param)
{
struct input *t=(struct input *)param;
int i;
max = 0;
for (i = 0; i < t->count; i++)
if (atoi(t->data[i])>max)
max=atoi(t->data[i]);
pthread_exit(0);
}
