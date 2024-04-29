#include "header.h"
struct sockaddr_in saddr;
struct ip_mreq group;
int ss;
sem_t mutex;
int flag=0;

void *rec(void *args)
{
	
	char buff[max];	
	struct sockaddr_in raddr=saddr;
	while(1)
	{
		//sem_wait(&mutex);
	        
		int length = sizeof(raddr);
		recvfrom(ss, buff, max, 0, (struct sockaddr *)&raddr, &length);
		if(!flag)
		printf("%s\n",buff);
		flag=0; 
		if(strstr(buff,"end")!=NULL)
		{
			printf("%s :left the chat\n\n",buff);
			break;
		}
		       
		//sem_post(&mutex);
	}
	pthread_exit(NULL);
	
}

void *sen(void *args)
{
        char buff[max];
	struct sockaddr_in seaddr=saddr;
	while(1)
	{
		//sem_wait(&mutex);
		fgets(buff, max, stdin);
		buff[strlen(buff)-1] = '\0';
		flag=1;
		char t[50]="Soumyadeep: ";
		strcat(t,buff);
		sendto(ss,t, max, 0, (struct sockaddr *)&seaddr, sizeof(seaddr));	
		if(strstr(buff,"end")!=NULL)
		        break;
		//printf("SUCCESS\n\n");
		//sem_post(&mutex);
	}
	pthread_exit(NULL);
	
}
int main(int argc, char **argv)
{
	sem_init(&mutex,0,1);
	if(argc<3)
	{
		printf("Insufficient Args\n\n");
		exit(1);
	}
	pthread_t pt1,pt2;
	
	ss = socket(AF_INET, SOCK_DGRAM, 0);
	
	
	// allow multiple sockets to use the same PORT number		
	/* Enable SO_REUSEADDR to allow multiple instances of this
           application to receive copies of the multicast datagrams. */

        saddr.sin_family=AF_INET;
	saddr.sin_addr.s_addr = inet_addr(argv[1]);//Change
	saddr.sin_port = htons(atoi(argv[2]));
	
	 int reuse = 1;
        if(setsockopt(ss, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0)
        {
                perror("Setting SO_REUSEADDR error");
                close(ss);
                exit(1);
        }
        else
                printf("Setting SO_REUSEADDR...OK.\n");
	
	bind(ss, (struct sockaddr *)&saddr, sizeof(saddr));
 
	
	/* Join the multicast group mip on the local sip
        interface. Note that this IP_ADD_MEMBERSHIP option must be
        called for each local interface over which the multicast
        datagrams are to be received. */

        group.imr_multiaddr.s_addr = inet_addr(argv[1]);
        group.imr_interface.s_addr = INADDR_ANY;

        if(setsockopt(ss, IPPROTO_IP, IP_ADD_MEMBERSHIP, &group, sizeof(group)) < 0)
        {
                perror("Adding multicast group error");
                close(ss);
                exit(1);
        }
        else
                printf("Adding multicast group...OK.\n");
        	
	
	printf("Enter the messages: \n");
	pthread_create(&pt2,NULL,rec,NULL);
	pthread_create(&pt1,NULL,sen, NULL);
        
     
	pthread_join(pt1,NULL);
	pthread_join(pt2,NULL);
	
	
	close(ss);
	
	printf("--::CHAT ENDS::--\n");
	return 0;
	
}
