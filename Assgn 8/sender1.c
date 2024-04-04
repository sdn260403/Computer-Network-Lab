#include "header.h"
struct sockaddr_in caddr;
int ss;
void *rec(void *args)
{
	
	char buff[max];	
	while(1)
	{
	              
		int length = sizeof(caddr);
		recvfrom(ss, buff, max, 0, (struct sockaddr *)&caddr, &length);

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
		
		if(!strcmp("exit",buff))
		        break;
		        
		
	}
	pthread_exit(NULL);
	
}
int main()
{
	pthread_t pt1,pt2;
	
	ss = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in saddr, daddr;
	struct in_addr localInterface;
	
	saddr.sin_family=AF_INET;
	saddr.sin_addr.s_addr = inet_addr(mip);
	saddr.sin_port = htons(sport);

	bind(ss, (struct sockaddr *)&saddr, sizeof(saddr));
	
	daddr.sin_family=AF_INET;
	daddr.sin_addr.s_addr = inet_addr(sip);
	daddr.sin_port = htons(dport);
	
	
	/* Set local interface for outbound multicast datagrams. 
         The IP address specified must be associated with a local,
         multicast capable interface. */

        localInterface.s_addr = inet_addr(sip);
        if(setsockopt(ss, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface, sizeof(localInterface)) < 0)
        {
                perror("Setting local interface error");
                exit(1);
        }
        else
                printf("Setting the local interface...OK\n");
                
                
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
