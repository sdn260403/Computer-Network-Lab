#include "header.h"


int main (){
	int  l, n, sid, cid;
	struct sockaddr_in saddr, caddr;
	char sip_addr[32], t, msg[32], res[32];

	strcpy(sip_addr, "127.0.0.1");
	
	sid = socket(AF_INET, SOCK_STREAM, 0);
	saddr.sin_family = AF_INET;
	
	//sad.sin_addr.s_addr = inet_addr (sip_addr);
	inet_aton(sip_addr, &(saddr.sin_addr));
	saddr.sin_port = htons(1234);
	
	bind(sid, (struct sockaddr *)&saddr, sizeof(saddr));
	
	listen(sid, 1);
	
	l = sizeof(caddr);
	
	printf("Starting...\n\n");
	//sleep(1);
	while(1)
	{
		cid = accept(sid, (struct sockaddr *)&caddr, &l);
		if(cid)
			printf("CONNECTION ESTABLISHED\n\n");
			
		n = read(cid, (void *)msg, sizeof(msg));
		msg[n] = 0;
		if(!strcmp(msg, "EXIT") || !strcmp(msg, "exit"))
		{
			printf("Signing Off...\n");
			sleep(1);
			break;
		}
		printf("Data Rec'vd\n\n");
		// Bit-stuffing and resending the message
		int i=0, j=0,cnt=0;
		while(msg[i]!='\0')
		{
			//cnt++;
			if(msg[i]=='1')
				cnt++;
			else
				cnt=0;
				
			res[j]=msg[i];
			if(cnt==5)
			{
				j++;
				res[j]='0';				
				cnt=0;
			}
			
			
			i++;
			j++;
		}
		res[j]='\0';
		printf("Data Sent\n\n");
		write(cid, (void *)res, sizeof(res));
		close(cid);
	}
	return 0;
}
