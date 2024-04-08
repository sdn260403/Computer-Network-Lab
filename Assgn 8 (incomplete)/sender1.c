#include "header.h"
struct sockaddr_in saddr,caddr;
int ss;
void *rec(void *args)
{
        char buff[max];	     
	int length = sizeof(caddr);
	while(1)
	{
	        
		recvfrom(ss, buff, max, 0, (struct sockaddr *)&saddr, &length);
		printf("SUCCESS\n\n");

		printf("%s\n", buff);
		        
		
	}
	pthread_exit(NULL);
	
}

void *sen(void *args)
{
	char buff[max];	
	while(1)
	{
		//printf("Enter the message: \n");
		fgets(buff, max, stdin);
		buff[strlen(buff)-1] = '\0';

		int len = sizeof(caddr);
		sendto(ss, buff, max, 0, (struct sockaddr *)&caddr, len);
		
		printf("SUCCESS\n\n");
		
		if(!strcmp("exit",buff))
		        break;
	}
	pthread_exit(NULL);
	
}
int main()
{
	pthread_t pt1,pt2;
	
	ss = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in daddr;
	struct in_addr localInterface;
	
	/*int reuse = 1;
        if(setsockopt(ss, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) < 0)
        {
                perror("Setting SO_REUSEADDR error");
                close(ss);
                exit(1);
        }
        else
                printf("Setting SO_REUSEADDR...OK.\n");*/
	
	saddr.sin_family=AF_INET;
	saddr.sin_addr.s_addr = inet_addr(mip);
	saddr.sin_port = htons(mport);

	
	
	daddr.sin_family=AF_INET;
	daddr.sin_addr.s_addr = htonl(INADDR_ANY);
	daddr.sin_port = htons(dport);
	
	bind(ss, (struct sockaddr *)&daddr, sizeof(daddr));
	
	
	/* Set local interface for outbound multicast datagrams. 
         The IP address specified must be associated with a local,
         multicast capable interface. */

       /* localInterface.s_addr = inet_addr(sip);
        if(setsockopt(ss, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface, sizeof(localInterface)) < 0)
        {
                perror("Setting local interface error");
                exit(1);
        }
        else
                printf("Setting the local interface...OK\n");*/
                
                
	caddr=daddr;
	
	printf("Server Starts...\n");
	
	pthread_create(&pt1,NULL,sen, NULL);
        pthread_create(&pt2,NULL,rec, NULL);
        
	pthread_join(pt1,NULL);
	pthread_cancel(pt2);
	
	close(ss);
	
	printf("--::Server ENDS::--\n");
	return 0;
	
}
