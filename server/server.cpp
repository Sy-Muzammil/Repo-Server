#include <stdio.h>
#include<iostream>
#include <stdlib.h>
#include <string.h>
#include<string>
#include<sstream>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include<fcntl.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include<fstream>
#include<vector>
#include<map>
#include<utility> 
//#include<cstdlib>
#include<arpa/inet.h> 
#include <cstddef>


using namespace std;
std::vector < pair < string , string > > myvector;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}
		/*log file maintainance*/
int log_file_search(char buffer[],char cli_addr[])
{
char buffer1[256];
    struct tm *sTm;

    time_t present = time (0);
    sTm = gmtime (&present);

    strftime (buffer1, sizeof(buffer1), "%Y-%m-%d %H:%M:%S", sTm);
ofstream out;
out.open("log.txt",ios_base::app);
out<<buffer1<<"##"<<cli_addr<<"##"<<"Search for:  "<<buffer<<"#\n";
out.flush();
return 0;
}


int log_file_update(char buffer[],char cli_addr[])
{
char buffer1[256];
    struct tm *sTm;

    time_t present = time (0);
    sTm = gmtime (&present);

    strftime (buffer1, sizeof(buffer1), "%Y-%m-%d %H:%M:%S", sTm);
ofstream out;
out.open("log.txt",ios_base::app);
out<<buffer1<<"##"<<cli_addr<<"##"<<"Update:  "<<buffer<<"#\n";
out.flush();
return 0;
}



	//***update repo.txt file***//***write entries in repo.txt***//

int update_repo(char buffer[],char *cli_addr)
{
//pair < string,string > image;
char filename[256],path[256],p[256],f[256];
int j,i,x,k;//fd,flag=0;
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
		
		for(k=0;k<j;k++)
		{
			path[i]=buffer[k];
			i++;
		}

		path[i]='\0';
		i=0;
		for(k=j;k<=x;k++)
		{
			filename[i]=buffer[k];
			i++;
		}
strcpy(p,path);
strcpy(f,filename);
strcat(p,f);
		//find if it is already present or not//
   /*  vector < pair < string,string > > :: iterator ite;
     for( ite = myvector.begin() ;ite != myvector.end();ite++)
	{
		if((ite->first.compare(cli_addr)==0) && (ite->second.compare(p)==0))
		{
			flag=1;
			break;
		}
     }

	if(flag==0)*/
myvector.push_back(make_pair(cli_addr,p));// writing in  data structure using vector//

		// writing in repo.txt //

ofstream out;
out.open("repo.txt",ios_base::app);
out<<f<<"#"<<cli_addr<<"#"<<p<<"#\n";
bzero(f,256);
bzero(p,256);
out.clear();
return 0;

}

void search(char buffer[],int newsockfd)
{
	int i=1,flag=0;
	string str1;
	string str2;
	string str4;
	
	vector < pair < string , string > > :: iterator ite;
		string n(buffer);
		for( ite = myvector.begin() ;ite != myvector.end();ite++)
			{
				//cout<<ite->second<<"\n";
				if(ite->second.find(n)+1)
				{
				stringstream ss;		
				ss << i;
				string str3 = ss.str();
			 	str1=str3+":  "+ite->first+"@"+ite->second+"\n";
			 		if(write(newsockfd,str1.c_str(),strlen(str1.c_str())) < 0)
  					{
  					printf("\nUnable to send");		
  					}
				sleep(1);
				flag=1;
				i++;
				str1.clear();
				}
			}
		shutdown(newsockfd,1);
		//str4="qwerty";
		//write(newsockfd,str4.c_str(),strlen(str4.c_str()));
		
	//	}		
	//}
	if(flag==0)	
	{
		str2="File does not exists\n";
		write(newsockfd,str2.c_str(),strlen(str2.c_str()));
	}
}


void start_update_repo()
{
int index1,index2,index3;//flag=0;
string line;
string cli_addr;
string file_path;
ifstream in;
in.open("repo.txt");
//std::vector < pair < string,string > > repo_again;
	 while(getline (in,line))
	 {
    	index1 = line.find("#");
     	index2 = line.find("#",index1+1);
    	cli_addr=line.substr(index1+1,index2-(index1+1));
    	index3 = line.find("#",index2+1);
    	file_path=line.substr(index2+1,index3-(index2+1));
    	
    	//repo_again.first=cli_addr;
    	//repo_again.second=path;
     	/*vector < pair < string,string > >  :: iterator ite;
	     	for( ite= myvector.begin() ; ite != myvector.end(); ite++)
			{
				if((ite->first.compare(cli_addr)==0) && ite->second.compare(file_path))
				{
					flag=1;
					break;
				}
     			}
     	if(flag==0)*/
     	myvector.push_back(make_pair(cli_addr,file_path));
     	line.clear();
     }   
}


int main(int argc, char *argv[])
{
int sockfd, newsockfd, portno;
socklen_t clilen;
char buffer[256],cl_addr[256];
char option[3];
struct sockaddr_in serv_addr,cli_addr;
//int n;
	if (argc < 2) 
	{
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     	}
     
sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
        	error("ERROR opening socket");
     
bzero((char *) &serv_addr, sizeof(serv_addr));
portno = atoi(argv[1]);

serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = INADDR_ANY;
serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
          error("ERROR on binding");
listen(sockfd,5);
clilen = sizeof(cli_addr);

start_update_repo();

newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);
	if (newsockfd < 0) 
        	  error("ERROR on accept");


     // reads from the client //
	bzero(buffer,256);
	
     //n = read(newsockfd,buffer,255);
     	//if (n < 0) error("ERROR reading from socket");
strcpy(cl_addr,inet_ntoa(cli_addr.sin_addr));

		//whether to search or update//
while(read(newsockfd,option,255))
    {
	
    	//read(newsockfd,option,255);
    	read(newsockfd,buffer,255);
    	switch(*option)
    	{
    		case '1':	search(buffer,newsockfd);
				log_file_search(buffer,cl_addr);
				bzero(buffer,256);
				break;
    		case '2':	update_repo(buffer,cl_addr);
				log_file_update(buffer,cl_addr);
				bzero(buffer,256);
 				break;
		case '3':   	exit(1);			
				break;
    	}
bzero(buffer,256);
    }

//std::cout<<"Here is the message:\n"<<buffer<<"\n";
 	
	
//after reading is successfull send ack to same address//
  //  n = write(newsockfd,"I got your message\n",25);

	//     if (n < 0) error("ERROR writing to socket");
	     close(newsockfd);

     close(sockfd);
     return 0; 
}
