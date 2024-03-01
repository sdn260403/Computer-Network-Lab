#include "header.h"

struct msg
{
	long int priority;
	int data;
};

int main()
{
	struct msg d1,d2,d3;
	int msgid;
	key_t k=ftok("memory",67);
	msgid = msgget(k, 0666 | IPC_CREAT);
	if (msgid == -1) 
	{
		printf("msgid ERROR");
		exit(EXIT_FAILURE);
	}

	
	
	d1.priority=1;
	printf("Enter Data in decimal: ");
	scanf("%d",&d1.data);
	if (msgsnd(msgid, (void *)&d1, BUFSIZ, 0) == -1) 
	{
		printf("msgsnd ERROR");
		exit(EXIT_FAILURE);
	}

	
	d2.priority=2;
	printf("Enter Data in decimal: ");
	scanf("%d",&d2.data);
	if (msgsnd(msgid, (void *)&d2, BUFSIZ, 0) == -1) 
	{
		printf("msgsnd ERROR");
		exit(EXIT_FAILURE);
	}


	d3.priority=3;
	printf("Enter Data in decimal: ");
	scanf("%d",&d3.data);
	if (msgsnd(msgid, (void *)&d3, BUFSIZ, 0) == -1) 
	{
		printf("msgsnd ERROR");
		exit(EXIT_FAILURE);
	}
	
	exit(EXIT_SUCCESS);
	
}
