#include <stdio.h>
#include<iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include<vector>
#include <sys/types.h>
#include <sys/stat.h>
#include<fcntl.h>
#define port_num 8000
using namespace std;
std::vector < pair < string , string > > myvector;

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

void download_file(string option,char path[],char cli_addr[])
{
char filename[256],buff[100];
int i,j,k,x;
x=strlen(path);
	for(i=0;i<x;i++)
	{
		if (path[i]=='/')
			j=i+1;
		if (path[i]=='.')
		{
			i=0;
			break;
		}
			
	}
		
		for(k=j;k<=x;k++)
		{
			filename[i]=path[k];
			i++;
		}
		//filename[i]='\0';


//char str[256];
int sockfd, newsockfd;
struct sockaddr_in serv_addr;
struct hostent *server;

sockfd = socket(AF_INET, SOCK_STREAM, 0);
server = gethostbyname(cli_addr);
bzero((char *) &serv_addr, sizeof(serv_addr));
serv_addr.sin_family = AF_INET;
bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
serv_addr.sin_port = htons(port_num);
if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) //connect to child server
        error("ERROR connecting");


write(sockfd,path,strlen(path));

int f=open(filename, O_RDWR | O_CREAT,0777);
while(read(sockfd,buff,1))
{
write(f,buff,1);
}	

close(sockfd);
close(f);
}


		//search results are displayed here//

void search_result(int sockfd)
{

char buffer[256],cli_addr[256],path[256],option[10];
int n,k=0,i,j;

	while(read(sockfd,buffer,255))
	{
		//if(strcmp(buffer,"qwerty"))
		//break;
	printf("%s\n",buffer);
	n=strlen(buffer);
		for(i=0;i<n;i++)
		{
			if (buffer[i]=='@')
			{
			j=i;
			break;
			}
		}

		for(i=0;i<j;i++)
			cli_addr[i]=buffer[i];
		cli_addr[i]='\0';
		
			for(i=j+1;i<n;i++)
			{
			path[k]=buffer[i];	
			k++;
			}
		path[k]='\0';
	myvector.push_back(make_pair(cli_addr,path));
	}
printf("Enter the choice you want to download: ");
scanf("%s",option);
//printf("%s\n",option);
download_file(option,path,cli_addr);
}


int main(int argc, char *argv[])
{


int sockfd, portno,n;
struct sockaddr_in serv_addr;
struct hostent *server;
char buffer[256];
    	if (argc < 3) 
	{
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    	}

int p_id=fork();
		//integrated client server//

if(p_id==0)
{
int sockfd, newsockfd, portno;
socklen_t clilen;
char buffer[256],cl_addr[256],path[256];
char option[3];
struct sockaddr_in serv_addr,cli_addr;
int n;
	
     
sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
        	error("ERROR opening socket");
     
bzero((char *) &serv_addr, sizeof(serv_addr));


serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = INADDR_ANY;
serv_addr.sin_port = htons(port_num);
if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
          error("ERROR on binding");
listen(sockfd,5);
clilen = sizeof(cli_addr);
newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);
	if (newsockfd < 0) 
        	  error("ERROR on accept");
read(newsockfd,path,255);
int f1=open(path,O_RDONLY);
char buff[100];
//int f2=open(,O_RDWR)
while(read(f1,buff,1))
{
write(newsockfd,buff,1);
}
}

		//parent client process//
if(p_id>0)
{
portno = atoi(argv[2]);
sockfd = socket(AF_INET, SOCK_STREAM, 0);
 
if (sockfd < 0) 
  error("ERROR opening socket");
 server = gethostbyname(argv[1]);
    
if (server == NULL) 
	{
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    	}
bzero((char *) &serv_addr, sizeof(serv_addr));
serv_addr.sin_family = AF_INET;
bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
serv_addr.sin_port = htons(portno);

    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) //connect to server
        error("ERROR connecting");
		
		while(1)
		{
		char c[10];
		std::cout<<"Select:\n1.Search\n2.Share\n3.Exit\n>> ";
		scanf("%s",c);
		write(sockfd,c,strlen(c));
		//printf("%c",c);
			switch(*c)
			{

			case '1'	: printf("Print the string to search for: ");
					  scanf("%s",buffer);
					  n = write(sockfd,buffer,strlen(buffer));
					  bzero(buffer,256);
						if (n < 0) 
						{
        			 		error("ERROR writing to socket");
						return 0;
						}
					search_result(sockfd);
					/* n = read(sockfd,buffer,255);
					if (n < 0) 
         				error("ERROR reading from socket");
    					printf("%s\n",buffer);
    					close(sockfd);*/
					break;

			case '2'	: printf("Print the Path: ");
					  scanf("%s",buffer);
					  n = write(sockfd,buffer,strlen(buffer));
						if (n < 0) 
						{
        					error("ERROR writing to socket");
						return 0;
						}
					bzero(buffer,256);
					/* n = read(sockfd,buffer,255);
					if (n < 0) 
         				error("ERROR reading from socket");
    					printf("%s\n",buffer);*/
    					//close(sockfd);
					break;
	
			case '3'	: 	exit(1);
					break;
		
			default : 	printf("Invalid choice \n");
				  	break;			
			}
		}
    /*
	std::cout<<"Please enter the message: ";
    
	bzero(buffer,256);
    	fgets(buffer,255,stdin);
    n = write(sockfd,buffer,strlen(buffer));//writes the message from client to server
    if (n < 0) 
         error("ERROR writing to socket");
    
	bzero(buffer,256);
    n = read(sockfd,buffer,255);//reads the ack from server//
    
	if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);
    close(sockfd);*/
}
    return 0;
}
