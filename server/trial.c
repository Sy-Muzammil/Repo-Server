#include<stdio.h>
int main()
{
char buffer[256];		
		while(1)
		{
		int c;
		printf("Select:\n1.Search\n2.Share\n3.Exit\n>> ");
		scanf("%d",&c);
		printf("%d\n",c);
			switch(c)
			{

			case 1	: 	printf("Print the string to search for: \n");
					//fgets(buffer,255,stdin);
					scanf("%s",buffer);
					printf("%s\n",buffer);
					/*n = write(sockfd,buffer,strlen(buffer));
					bzero(buffer,256);
						if (n < 0) 
						{
        			 		error("ERROR writing to socket");
						return 0;
						}*/
					break;

			case 2	: 	printf("Print the Path:\n");
					/*fgets(buffer,255,stdin);
					n = write(sockfd,buffer,strlen(buffer));
					bzero(buffer,256);
						if (n < 0) 
						{
        					error("ERROR writing to socket");
						return 0;
						}*/
					break;
	
			//case 3	: 	exit(1);
			//		break;
		
			default : 	printf("Invalid choice \n");
				  	break;			
			}
		}
return 0;
}
