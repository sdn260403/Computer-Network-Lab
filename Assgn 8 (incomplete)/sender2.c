#include "header.h"
struct sockaddr_in saddr,caddr;
int ss;

void *rec(void *args)
{
	
	char buff[max];	
	while(1)
	{
	        
		int length = sizeof(caddr);
		recvfrom(ss, buff, max, 0, (struct sockaddr *)&caddr, &length);
		printf("Server : %s\n",buff);
		
		if(!strcmp("exit",buff))
		        break;        
		
	}
	pthread_exit(NULL);
	
}

void *sen(void *args)
{
        char buff[max];
		
	while(1)
	{
	        char t[50]="Client1: ";
	        
		fgets(buff, max, stdin);
		buff[strlen(buff)-1] = '\0';
		
		//printf("%s\n", buff);                
		int len = sizeof(caddr);
		strcat(t,buff);
		
		sendto(ss,t, max, 0, (struct sockaddr *)&caddr, len);	
		printf("SUCCESS\n\n");
	}
	pthread_exit(NULL);
	
}
int main()
{
	pthread_t pt1,pt2;
	
	ss = socket(AF_INET, SOCK_DGRAM, 0);
	struct ip_mreq group;
	
	// allow multiple sockets to use the same PORT number		
	/* Enable SO_REUSEADDR to allow multiple instances of this
           application to receive copies of the multicast datagrams. */

        int reuse = 1;
        if(setsockopt(ss, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) < 0)
        {
                perror("Setting SO_REUSEADDR error");
                close(ss);
                exit(1);
        }
        else
                printf("Setting SO_REUSEADDR...OK.\n");

        saddr.sin_family=AF_INET;
	saddr.sin_addr.s_addr = inet_addr(sip);//Change
	saddr.sin_port = htons(dport);
	
	caddr.sin_family=AF_INET;
	caddr.sin_addr.s_addr = htonl(INADDR_ANY);//change
	caddr.sin_port = htons(mport);
	
	bind(ss, (struct sockaddr *)&saddr, sizeof(saddr));
 
	
	/* Join the multicast group mip on the local sip
        interface. Note that this IP_ADD_MEMBERSHIP option must be
        called for each local interface over which the multicast
        datagrams are to be received. */

        group.imr_multiaddr.s_addr = inet_addr(mip);
        group.imr_interface.s_addr = htonl(INADDR_ANY);

        if(setsockopt(ss, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group, sizeof(group)) < 0)
        {
                perror("Adding multicast group error");
                close(ss);
                exit(1);
        }
        else
                printf("Adding multicast group...OK.\n");
        	
	
	printf("Enter the messages: \n");
	pthread_create(&pt1,NULL,sen, NULL);
        pthread_create(&pt2,NULL,rec,NULL);
     
	pthread_join(pt2,NULL);
	pthread_cancel(pt1);
	
	
	close(ss);
	
	printf("--::CHAT ENDS::--\n");
	return 0;
	
}
