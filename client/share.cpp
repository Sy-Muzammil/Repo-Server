#include<stdio.h>
#include<iostream>
#include<string.h>
int main()
{
char buffer[256],filename[256],path[256];
int j,i,x,k;
printf("Print the path: ");
scanf("%s",buffer);
x=strlen(buffer);
	for(i=0;i<x;i++)
	{
		if (buffer[i]=='/')
			j=i+1;
		if (buffer[i]=='.')
		{
			i=0;
			break;
		}
			
	}
		/*path[i]='#';
		path[i+1]='#';
		i++;*/
		for(k=0;k<j;k++)
		{
			path[i]=buffer[k];
			i++;
		}
		
		/*path[i]='#';
		path[i+1]='#';*/
		path[i]='\0';
		i=0;
		//filename[i]='#';
		//filename[i+1]='#';
		//i++;
		for(k=j;k<=x;k++)
		{
			filename[i]=buffer[k];
			i++;
		}
		
	//	filename[i]='#';
	//	filename[i+1]='#';
	//	filename[i+1]='\0';
		
	printf("%s\n",path);
	printf("%s\n",filename);
return 0;
}
