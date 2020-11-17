#include<stdio.h>
#include<stdlib.h>

int findFIFO(int pos,int k,int frames[],int ref_str[],int ref_cnt,int prev)
{
 int a=frames[pos],b=frames[k];
 for(int i=prev;i<ref_cnt;i++)
 {   if(ref_str[i]==a)
       return pos;
    else if(ref_str[i]==b)
       return k;
 }
}

void display(int frames[],int nof)
{
	   for(int x=0;x<nof;x++)
		 {
		 if(frames[x]==-1)
		     printf("X ");
		 else
		 		printf("%d ",frames[x]);
		 }
		 printf("\n"); 
}

void changeFreq(int ref,int element[],int freq[],int ref_cnt)
{
	int i,j;
	for(i=0;i<ref_cnt;i++)
	{
		if(element[i]!=-1 && element[i] ==ref)
		{
		 freq[i]++;
		 break;
		}
		else if(element[i]==-1)
		{
		 element[i]=ref;
		 freq[i]++;
		 break;
		}
	}
}

int main()
{
int no_ff,nof, ref_str[20],ref_cnt=-1;
int i,j,k,x,min,flag,pos, pf=0,prev=0;

printf("Enter the number of free frames: ");
scanf("%d",&no_ff);
printf("Enter the number of frames required by the process: ");
scanf("%d",&nof);
int frames[nof];

for(i=0;i<nof;i++)
	frames[i]=-1; 
	 
if(no_ff<nof)
{
 printf("No of frames required is greater than free frames available!");
 exit(1);
}

printf("\nEnter the reference string : ");
do
{
 scanf("%d",&ref_str[++ref_cnt]); 
}while(ref_str[ref_cnt]!=-1);
printf("\n");

int element[ref_cnt];
int freq[ref_cnt];

for(i=0;i<ref_cnt;i++)
{
element[i]=-1;
freq[i]=0;
}

for(i=0;i<ref_cnt;i++)
{
 for(pos=0;pos<nof;pos++)
 {
  	if(frames[pos]==ref_str[i]) //if that page is found
    {  changeFreq(ref_str[i],element,freq,ref_cnt);
       break;        
    }
 }
 
 if(pos==nof)        //if page not found
 {
  for(pos=0;pos<nof;pos++)          // If there is space available in frames.
   	if(frames[pos]==-1) 
  			break;
	 		
  min=999;
  if(pos==nof)  // If there is no available frame---replace
  {
   for(k=0;k<nof;k++)          // If there is space available in frames.
   {
    flag=0;
    for(x=0;x<ref_cnt;x++)
    {
   	 if(frames[k]==element[x])
   	 {
   	  if(freq[x]<min)
   	  {
   	   min=freq[x];
   	   pos=k;
   	  }
   	  else if(freq[x]==min)
   	  {
   	   pos=findFIFO(pos,k,frames,ref_str,ref_cnt,prev);
   	   prev=pos;
   	  }
   	  flag=1;
   	 }
   	 if(flag==1)
   	 	 break;
    }
   }
	} //end if pos==nof
   frames[pos]=ref_str[i];
   pf++;
	 printf("\nPage fault in inserting page %d in pos %d- ",ref_str[i],pos); 
   display(frames,nof);
	 changeFreq(ref_str[i],element,freq,ref_cnt);  
	}//if(pos==nof)  //if page not found
}//end for ref_str
	
printf("\nThe number of page faults using lfu are %d\n",pf);
return 0;
}

/*

#include<stdio.h>
void main()
{
int rs[50], i, j, k, m, f, cntr[20], a[20], min, pf=0;
clrscr();
printf("\nEnter number of page references -- ");
scanf("%d",&m);
printf("\nEnter the reference string -- ");
for(i=0;i<m;i++)
scanf("%d",&rs[i]);
printf("\nEnter the available no. of frames -- ");
scanf("%d",&f);
for(i=0;i<f;i++)
{
cntr[i]=0;
a[i]=-1;
}
Printf(“\nThe Page Replacement Process is – \n“);
for(i=0;i<m;i++)
{
for(j=0;j<f;j++)
if(rs[i]==a[j])
{
cntr[j]++;
break;
}
if(j==f)
{
min = 0;
for(k=1;k<f;k++)
if(cntr[k]<cntr[min])
min=k;
a[min]=rs[i];
cntr[min]=1;
pf++;
}
printf("\n");
for(j=0;j<f;j++)
printf("\t%d",a[j]);
if(j==f)
printf(“\tPF No. %d”,pf);
}
printf("\n\n Total number of page faults -- %d",pf);
}

*/
