#include "header.h"
struct sockaddr_in caddr;
int ss;
sem_t x,y;
void *rec(void *args)
{
	
	char buff[max];	
	while(1)
	{
	        
		int length = sizeof(caddr);
		if(recvfrom(ss, buff, max, 0, (struct sockaddr *)&caddr, &length)>0)
		{
                        sem_wait(&x);
		        printf("\nClient %d : %s\n",*(int *)args, buff);
		        sem_post(&x);
		}
		if(!strcmp("exit",buff))
		        break;
		 
		        
		
	}
	pthread_exit(NULL);
	
}

void *sen(void *args)
{
		
	while(1)
	{
	        sem_wait(&y);
	       // sem_wait(&x);
	        char t[50]="Client: ";
	        /*char *tx=(char *)(int *) args;
	        strcat(t,tx);
	        strcat(t,": ");*/
	        printf("Enter Message: ");//%d ",*(int*) args);
	        sem_post(&x);
	        sleep(2);
	        char buff[max];
		fgets(buff, max, stdin);
		buff[strlen(buff)-1] = '\0';
		
		//printf("%s\n", buff);
                
		int len = sizeof(caddr);
		
		sendto(ss,strcat(t,buff), max, 0, (struct sockaddr *)&caddr, len);
		sem_wait(&x);
		sem_post(&y);
		sleep(2);
		//sem_post(&x);
		
		
	}
	pthread_exit(NULL);
	
}
int main()
{
	pthread_t pt1[N],pt2[N];
        sem_init(&y, 0, 1);
        sem_init(&x, 0, 1);
        int i=0;
	
	ss = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in saddr, daddr;
	struct ip_mreq group;
		
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
	saddr.sin_addr.s_addr = inet_addr(sip);
	saddr.sin_port = htons(dport);
	
	daddr.sin_family=AF_INET;
	daddr.sin_addr.s_addr = inet_addr(mip);
	daddr.sin_port = htons(sport);
	
	caddr=daddr;
	
	bind(ss, (struct sockaddr *)&daddr, sizeof(daddr));
	
 
	
	/* Join the multicast group mip on the local sip
        interface. Note that this IP_ADD_MEMBERSHIP option must be
        called for each local interface over which the multicast
        datagrams are to be received. */

        group.imr_multiaddr.s_addr = inet_addr(mip);
        group.imr_interface.s_addr = inet_addr(sip);

        if(setsockopt(ss, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group, sizeof(group)) < 0)
        {
                perror("Adding multicast group error");
                close(ss);
                exit(1);
        }
        else
                printf("Adding multicast group...OK.\n");
        	
	
	//printf("Enter the messages: \n");
	for(i=1;i<=N;i++)
	{
	        pthread_create(&pt1[i-1],NULL,sen, NULL);//(void *)&i);
                pthread_create(&pt2[i-1],NULL,rec,NULL);// (void *)&i);
        }
        
	for(i=0;i<N;i++)
	{
	        pthread_join(pt2[i],NULL);
	        pthread_cancel(pt1[i]);
	}
	
	close(ss);
	
	printf("--::CHAT ENDS::--\n");
	return 0;
	
}
