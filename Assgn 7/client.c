#include "header.h"

void main(){
	
	int cs = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	struct sockaddr_in saddr, caddr;
	saddr.sin_family=AF_INET;
	saddr.sin_addr.s_addr = inet_addr(ip);
	saddr.sin_port = htons(sport);

	//connect(cs, (struct sockaddr *)&saddr, sizeof(saddr));

	
		char buff[max];
		
		printf("Enter the message: \n");
		fgets(buff, max, stdin);
		buff[strlen(buff)-1] = '\0';

		int len = sizeof(saddr);
		sendto(cs, buff, max, 0, (struct sockaddr *)&saddr, len);
                if(!strcmp("exit",buff))
		{
		        close(cs);
		        exit(0);
		        
		}
		recvfrom(cs, buff, max, 0, (struct sockaddr *)&saddr, &len);

		printf("Message from server: %s\n", buff);

		
	
	close(cs);
}
