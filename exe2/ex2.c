#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h> 
//if we want to prints information about a signal 
//void psignal(unsigned sig, const char *s);

void main()
{
int pid,ppid,n,status,tid;
n=fork();
if(n!=0)
 printf("\nThis is the parent");
else
 printf("\nThis is the child");
pid=getpid();
ppid=getppid();
printf("\nPID: %d\n",pid);
printf("PARENT'S PID: %d\n",ppid);
tid=wait(&status);
if(tid!=-1)
{
printf("\nPID OF TERMINATED CHILD: %d\n",tid);
if(WIFEXITED(status))
 printf("Child terminated normally\tExit status: %d\n",WEXITSTATUS(status));
else if(WIFSIGNALED(status))
 printf("Child process was terminated by a signal\tNumber of the signal: %d",WTERMSIG(status));
else if(WIFSTOPPED(status))
 printf("Child process was stopped by delivery of a signal\tNumber of the stop signal: %d",WSTOPSIG(status));
}
}

