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

		printf("E1: %s\n", buff);
		
		if(!strcmp("bye",buff))
		{
		        close(ss);
		        pthread_exit(NULL);
		        
		}
		
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
		{
		        close(ss);
		        pthread_exit(NULL);
		        
		}
		
	}
	pthread_exit(NULL);
	
}
int main()
{
	pthread_t pt1,pt2;
	
	ss = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in saddr, daddr;
	saddr.sin_family=AF_INET;
	saddr.sin_addr.s_addr = inet_addr(sip);
	saddr.sin_port = htons(sport);

	bind(ss, (struct sockaddr *)&saddr, sizeof(saddr));
	
	daddr.sin_family=AF_INET;
	daddr.sin_addr.s_addr = inet_addr(cip);
	daddr.sin_port = htons(dport);
	
	caddr=daddr;
	
	//printf("Server Starts...\n");
	
	pthread_create(&pt1,NULL,sen, NULL);
        pthread_create(&pt2,NULL,rec, NULL);
        
	pthread_join(pt1,NULL);
	pthread_join(pt1,NULL);
	
	printf("--::CHAT ENDS::--\n");
	return 0;
	
}
