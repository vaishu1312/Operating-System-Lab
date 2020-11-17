#include<stdio.h>
#include<stdlib.h>
 
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
 
// to find the frame that will not be used recently in future after given index in ref_str
int predict(int ref_str[], int frames[], int ref_cnt, int nof,int index) 
{ 
  int j,pos = -1, far_idx = index; 
  for (int i = 0; i <nof; i++) 
  { 
   for (j = index; j < ref_cnt; j++) 
   { 
    if (frames[i] == ref_str[j]) 
    { 
		  if (j > far_idx) 
		  { 
		    far_idx = j; 
		    pos = i; 
		  } 
      break; 
    } 
   } 
  // If a page is never referenced in future, return it. 
  if (j == ref_cnt) 
        return i; 
  } 
  return pos; 
} 

int main() 
{
int no_ff,nof, ref_str[20],ref_cnt=-1;
int i,j,k,pos,pf=0;

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
 
// Traverse through page reference array and check for miss and hit. 
for (int i = 0; i < ref_cnt; i++) 
{ 
  for(j=0;j<nof;j++)
   	if(frames[j]==ref_str[i]) //if that page is found
	      break;     	  
	if(j!=nof)       //if that page is found     
	  continue; 
  // Page not found in a frame : MISS 
  // If there is space available in frames.
  for(k=0;k<nof;k++)
  {
   	if(frames[k]==-1) 
   	{
   		frames[k]=ref_str[i];
   		pf++;
			printf("Page fault in inserting page %d - ",ref_str[i]); 
			display(frames,nof);  
			break;
		} 		
  }
   // If there is no available frame---replace
  if(k==nof)
  { 
    pos = predict(ref_str, frames, ref_cnt, nof,i + 1); 
    frames[pos] = ref_str[i]; 
   	pf++;
		printf("Page fault in inserting page %d - ",ref_str[i]); 
		display(frames,nof);    
  } 
} 
printf("\nThe number of page faults using optimal are %d\n",pf);
return 0; 
}
