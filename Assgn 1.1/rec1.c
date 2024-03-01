#include "header.h"

struct msg
{
	long int priority;
	int data;
};

int main()
{
	struct msg d;
	int msgid,res[BUFSIZ],i,count=0;
	
	key_t k=ftok("memory",67);
	msgid = msgget(k, 0666 | IPC_CREAT);
	
	if (msgid == -1) 
	{
		printf("msgrcv failed with error\n”]");
		exit(EXIT_FAILURE);
	}
	
	if (msgrcv(msgid, (void *)&d, BUFSIZ,1, 0) == -1) 
	{
		printf("msgrcv failed with error\n");
		exit(EXIT_FAILURE);
	}
	
	printf("Message Received: %d\n",d.data);
	i=d.data;
	
	while(i>0)
	{
		res[count]=i%2;
		i/=2;
		count+=1;
	}
	for(i=count-1;i>=0;i--)
		printf("%d",res[i]);
	printf("\n");
	
	exit(EXIT_SUCCESS);
}
