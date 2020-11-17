#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
char fname[10];
}File;

typedef struct directory Directory;

struct directory{
char dname[10];
Directory *d1,*d2,*d3;
File *f1,*f2;
};

Directory *root = NULL;

Directory* get_directory_pointer(char s[])
{
	Directory *temp = root;
	char *token = strtok(s,"/");
	token = strtok(NULL,"/");
		
	while(token != NULL)
	{
		if(temp->d1 != NULL && strcmp(token,temp->d1->dname)==0)
			temp = temp->d1;
		else if(temp->d2 != NULL && strcmp(token,temp->d2->dname)==0)
			temp = temp->d2;
		else if(temp->d3 != NULL && strcmp(token,temp->d3->dname)==0)
			temp = temp->d3;
		else
			temp=NULL;
		token = strtok(NULL,"/");
	} //end while
	return temp;
}

File* get_file_pointer(char s[])
{
	Directory *temp = root;
	char *gstr;
	char *token = strtok(s,"/");
	token = strtok(NULL,"/");
	
	while(token != NULL) 
	{
		if(temp->d1 != NULL && strcmp(token,temp->d1->dname)==0)
			temp = temp->d1;
		else if(temp->d2 != NULL && strcmp(token,temp->d2->dname)==0)
			temp = temp->d2;
		else if(temp->d3 != NULL && strcmp(token,temp->d3->dname)==0)
			temp=temp->d3;
		gstr = token;
		token = strtok(NULL,"/");
	}
	
	if(temp->f1 != NULL && strcmp(temp->f1->fname,gstr)==0)
			return temp->f1;
	else if(temp->f2 != NULL && strcmp(temp->f2->fname,gstr)==0)
			return temp->f2;
	else
			return NULL;
}

void insert_directory(char str[])
{
	Directory* temp=root;
	char dstr[10];

	temp=get_directory_pointer(str);
	
	if(temp==NULL)
	{
	 printf("\nNo such directory!");
	 return;
	}

//	if(token==NULL)
//	{
		if(temp->d1==NULL||temp->d2==NULL||temp->d3==NULL)
		{
			printf("Enter the directory name: ");
			scanf("%s",dstr);
			Directory* newdir = (Directory*)malloc(sizeof(Directory));
			strcpy(newdir->dname,dstr);
			newdir->d1=newdir->d2=newdir->d3=NULL;
			newdir->f1=newdir->f2=NULL;
			if(temp->d1 == NULL)
				temp->d1 = newdir;
			else if(temp->d2 == NULL && strcmp(dstr,temp->d1->dname)!=0)
				temp->d2 = newdir;
			else if(strcmp(dstr,temp->d1->dname) != 0 && strcmp(dstr,temp->d2->dname)!=0)
				temp->d3 = newdir;
			else    //if(strcmp(dstr,temp->d1->dname) == 0 || strcmp(dstr,temp->d2->dname)==0)
				printf("Duplicate directories not allowed!\n");
		} //end if d1 d2 d3 null
		else
		 printf("Directory limit exceeded!\n");
//	} //end if token null
}

void insert_file(char str[])
{
	Directory* temp=root;
	char temp1[100],fstr[10];
	strcpy(temp1,str);

	char *token = strtok(temp1,"/");
	token = strtok(NULL,"/");
	
	if(token == NULL)
	{
	 printf("\nCannot create file in root directory");
	 return;
	}

	temp=get_directory_pointer(str);   //temp points to the directory in which insertion is to be done
	
	if(temp==NULL)
	{
	 printf("\nNo such directory!");
	 return;
	}
	
//	if(token == NULL)
//	{
		if(temp->f1 == NULL || temp->f2 == NULL)
		{
			printf("Enter the file name: ");
			scanf("%s",fstr);
			File *newfile = (File*)malloc(sizeof(File));
			strcpy(newfile->fname,fstr);
			if(temp->f1 == NULL)
				temp->f1=newfile;
			else if(temp->f2 == NULL && strcmp(fstr,temp->f1->fname)!=0)
				temp->f2=newfile;
			else
				printf("\nDuplicate files not allowed");
		}
		else
			printf("\nFile limit exceeded!");
//	}
}

/*void display_file(File* f, char s[])
{
printf("%-25s %s\n",s,f->fname);
}*/

void display(Directory* r, char s[])
{
	if(r!=NULL)
	{
		strcat(s,r->dname);
		strcat(s,"/");
		if(r->f1 != NULL)
			printf("%-25s %s\n",s,r->f1->fname); //display_file(r->f1,s);
		if(r->f2!=NULL)
			printf("%-25s %s\n",s,r->f2->fname); //display_file(r->f2,s);
		if(r->d1 != NULL) 
		{
			char s1[50];
			strcpy(s1, s);
			display(r->d1,s1);
		}
		if(r->d2 != NULL) 
		{
			char s1[50];
			strcpy(s1, s);
			display(r->d2,s1);
		}
		if(r->d3 != NULL) 
		{
			char s1[50];
			strcpy(s1, s);
			display(r->d3,s1);
		}
		if(r->f1 == NULL && r->d1== NULL)
				printf("%-25s EMPTY\n",s);
	}
}

void create_link(char s1[], char s2[])
{
	char a[300];
	File* f1 = get_file_pointer(s1);
	Directory* d2 = get_directory_pointer(s2);
	if(f1 != NULL) 
	{
	 if(d2!=NULL)
	 {
		if(d2->f1 == NULL)
			d2->f1 = f1;
		else if(d2->f2 == NULL)
			d2->f2 = f1;
		else
			printf("\nNot enough space in directory %s to make the link!\n",d2->dname);
	 } //end if d2
	 else
	 	 printf("\nNo such directory!\n");
	}  //end if f1
	else
			printf("\nNo such file!\n");	
}

int main()
{
	root = (Directory*)malloc(sizeof(Directory));
	strcpy(root->dname,"root");
	root->d1=root->d2=root->d3=NULL;
	root->f1=root->f2=NULL;
	int ch;
	while(1)
	{
		printf("\n\nDAG ORGANIZATION\n");
		printf("\n1.Create a directory\n2.Create a file\n3.Create a link to a file\n4.Search a file\n5.Search and display a directory\n6.Display all files\n7.Exit\n");
		printf("\nEnter your choice: ");
		scanf("%d",&ch);

		if(ch==1)
		{
			char path[50];
			printf("\n***Path format***\n");
			printf("root/ (or) root - to insert in root\n");
			printf("root/directory/ - to insert into directory in root\n");
			printf("Enter the path: ");
			scanf("%s",path);
			insert_directory(path);
		}
		else if(ch==2)
		{
			char path[50];
			printf("\n***Path format***\n");
			printf("root/directory/ - to insert file into directory in root\n");
			printf("Enter the path: ");
			scanf("%s",path);
			insert_file(path);
		}
		else if(ch==3)
		{
			char s1[50],s2[50];
			printf("Enter path of the file (including file name): ");
			scanf("%s",s1);
			printf("Enter path of directory to create link in: ");
			scanf("%s",s2);
			create_link(s1,s2);
		}
		else if(ch==4)
		{
			char path[50];
			printf("\n***Path format***\n");
			printf("root/directory/file - to search a file in a directory\n");
			printf("Enter the path: ");
			scanf("%s",path);
			File* fp=get_file_pointer(path);
			if(fp!=NULL)
				printf("\nFile %s found!",fp->fname);
			else
				printf("\nNo such file!\n");			
		}
		else if(ch==5)
		{
			char path[50],s[100];
			strcpy(s,"");
			printf("\n***Path format***\n");
			printf("root/directory - to search a directory\n");
			printf("Enter the path: ");
			scanf("%s",path);
			Directory* dp= get_directory_pointer(path);
			if(dp!=NULL)
			{
				printf("\nDirectory %s found!\n",dp->dname);
				printf("\nDirectory Path\t\tFile\n\n");
				display(dp,s);
			}
			else
				printf("\nNo such directory!\n");			
		}
		else if(ch==6)
		{
			char str[100];
			strcpy(str,"");
			printf("\nDirectory Path\t\tFile\n\n");
			display(root,str);
		}
		else
			break;
	}
}
