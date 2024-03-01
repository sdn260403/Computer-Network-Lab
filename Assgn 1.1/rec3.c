#include "header.h"

struct msg
{
	long int priority;
	int data;
};

int main()
{
	struct msg d;
	int msgid,i,count=0;
	char res[BUFSIZ];
	
	key_t k=ftok("memory",67);
	msgid = msgget(k,IPC_CREAT);
	
	if (msgid == -1) 
	{
		printf("msgrcv failed with error\n”]");
		exit(EXIT_FAILURE);
	}
	
	if (msgrcv(msgid, (void *)&d, BUFSIZ,3, 0) == -1) 
	{
		printf("msgrcv failed with error\n");
		exit(EXIT_FAILURE);
	}
	
	printf("Message Received: %d\n",d.data);
	i=d.data;
	printf("%x",i);
	printf("\n");
	
	exit(EXIT_SUCCESS);
}
