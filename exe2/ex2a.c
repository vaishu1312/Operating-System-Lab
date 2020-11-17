#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h> 

int fact(int n)
{
 if(n<=1)
   return 1;
 else
  return n*fact(n-1);
}

void main()
{
int a,b,c,d,n,i;
a=fork();
if(a==0)
{ printf("\nThis is the process A.\nEnter a number: ");
  scanf("%d",&n);   
  b=fork();
  if(b==0)
  {
   printf("\nThis is the process B.\nThe sum of first %d natural nos is: %d\n",n,n*(n+1)/2);   
   c=fork();
   if(c==0)
   { printf("\nThis is the process C.\nThe %dth multiplication table is: \n",n);
     for(i=1;i<=10;i++)
       printf("%d * %d = %d\n",n,i,n*i);  
     d=fork();
     if(d==0)
        printf("\nThis is the process D.\nThe factorial of %d is: %d\n",n,fact(n));   
   }  //end if c
   }  //end if b
}  //end if a
wait(NULL);
}

