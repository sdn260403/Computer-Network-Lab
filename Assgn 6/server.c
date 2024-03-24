#include "header.h"

int main (){
	int  l, n, sid, cid;
	struct sockaddr_in saddr, caddr;
	struct in_addr ip;
	char sip_addr[32],msg[32], res[32];

	strcpy(sip_addr, "127.0.0.1");
	
	sid = socket(AF_INET, SOCK_STREAM, 0);
	saddr.sin_family = AF_INET;
	
	//sad.sin_addr.s_addr = inet_addr (sip_addr);
	inet_aton(sip_addr, &(saddr.sin_addr));
	saddr.sin_port = htons(1234);
	
	bind(sid, (struct sockaddr *)&saddr, sizeof(saddr));
	
	listen(sid, 5);
	
	l = sizeof(caddr);
	
	printf("Starting...\n\n");
	
	signal(SIGCHLD,SIG_IGN);
	//sleep(1);
	while(1)
	{
		cid = accept(sid, (struct sockaddr *)&caddr, &l);
		if(cid)
			printf("CONNECTION ESTABLISHED\n\n");
		if(fork()==0)
		{		
			n = read(cid, (void *)msg, sizeof(msg));
			if(!strcmp(msg, "EXIT") || !strcmp(msg, "exit"))
			{
				printf("Signing Off...\n");
				break;
			}
			printf("Data Rec'vd\n\n");
			
			// Checking and resending the message
			if(inet_pton(AF_INET,msg,&ip)==1)
				strcpy(res,"YES");
			else
				strcpy(res,"NO");
				
			printf("Data Sent\n\n");
			write(cid, (void *)res, sizeof(res));
			close(cid);
		}
		else
			close(cid);
	}
	close(sid);
}
