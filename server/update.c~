#include<stdio.h>
#include<iostream>
#include<string.h>
#include<fcntl.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
char buffer[256],filename[256],path[256],p[256],f[256];
int fd;
scanf("%s %s",filename,path);
strcpy(p,path);
strcpy(f,filename);
strcat(p,f);
strcat(filename,"##");
strcat(path,"##");
strcat(filename,path);
fd=open(p, O_RDWR);
write(fd,filename,strlen(filename));
return 0;
}

