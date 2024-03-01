#include "header.h"

int compare(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}


int main()
{
	int msgid,i;
	struct roll rno,rno1;
	struct total t;
	long int p=2;
	
	key_t k=ftok("memory",67);
	msgid = msgget(k, 0666 | IPC_CREAT);
	if (msgid == -1) 
	{
		printf("msgid ERROR");
		exit(EXIT_FAILURE);
	}
        
        if(msgrcv(msgid,(void *)&t,512,4,0)==-1)
	{
	        printf("total read error\n");
	        exit(1);
	}
        int a[t.tot];
	
	for(i=0;i<t.tot;i++)
	{
	        
	        if(msgrcv(msgid,(void *)&rno,BUFSIZ,p,0)==-1)
	        {
	                printf("Roll Number Read error\n");
	            
	                exit(1);
	        }
	        printf("Received Roll No.: %d\n",rno.r);
	        a[i]=rno.r;
	        
	}
	
	qsort(a,t.tot,sizeof(int), compare);

	printf("After sorting\n");
	for(i=0;i<t.tot;i++)
	{
		printf("%d\n",a[i]);
	}

	printf("\n");
	
	for(i=0;i<t.tot;i++)
	{
	        rno1.r=a[i];
	        rno1.rp=6;
	        
	        if(msgsnd(msgid,(void *)&rno1,BUFSIZ,0)==-1)
	        {
	                printf("Roll number cannot be sent in queue\n");
	                exit(1);
	        }
	        
	}
	printf("Roll number sent\n");
	exit(EXIT_SUCCESS);
	
}
