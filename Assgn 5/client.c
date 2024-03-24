#include "header.h"


int main ()
{
	struct sockaddr_in saddr;
	int sid, i, j, n;
	char sip_addr[32], msg[32], t;

	strcpy(sip_addr, "127.0.0.1");
	

	sid = socket(AF_INET, SOCK_STREAM, 0);
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = inet_addr(sip_addr);
	saddr.sin_port = htons(1234);
	connect (sid, (struct sockaddr *)&saddr, sizeof(saddr));

	printf("Enter the message data to be sent: ");
	fgets (msg, sizeof(msg), stdin);
	msg[strlen(msg)-1]=0;
	write(sid, (void *)msg, sizeof(msg));
	
	n = read(sid, (void *)msg, sizeof(msg));
	msg[n] = 0;
	printf("\nBit-stuffed data returned from server: %s\n\n", msg);
	
	close(sid);
	return 0;
} 
