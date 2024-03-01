#include "header.h"
int compare(const void *a, const void *b)
{
	return strcmp(*(const char **)a, *(const char **)b);
}

int main()
{
	int msgid,i;
	struct name n,n1;
	struct total t;
	char name[BUFSIZ];
	long int p=1;
	
	key_t k=ftok("memory",67);
	msgid = msgget(k, 0666 | IPC_CREAT);
	if (msgid == -1) 
	{
		printf("msgid ERROR");
		exit(EXIT_FAILURE);
	}
	
	if(msgrcv(msgid,(void *)&t,512,3,0)==-1)
	{
	        printf("total read error\n");
	        exit(1);
	}
	char **a;
	a=(char**)malloc(t.tot*sizeof(char*));
	

	for(i=0;i<t.tot;i++)
	{
	        if(msgrcv(msgid,(void *)&n,BUFSIZ,p,0)==-1)
	        {
	                printf("Name Read error\n");
	                exit(1);
	        }
	        
	        //printf("Received Name : %s\n",n.N);
		a[i]=(char *)malloc(strlen(n.N) + 1);
		strcpy(a[i],n.N);
		printf("Received Name : %s\n",a[i]);
		
	        
	}
	
	qsort(a,t.tot,sizeof(char *),compare);

	printf("After sorting\n");
	for(i=0;i<t.tot;i++)
	{
		printf("%s\n",a[i]);
	}
	//getchar();
	printf("\n");
	
	for(i=0;i<t.tot;i++)
	{	        
	        n1.np=5;
	        strcpy(n1.N,a[i]);
	        printf("%s\n",n1.N);
	        while(msgsnd(msgid,(void *)&n1,MAX,0)!=0)
	        {
	                printf("Name cannot be sent in queue\n");
	                exit(1);
	        }
	        //else
	                printf("Name %s sent successfully\n",n1.N);
	        
	}
	printf("names sent\n");
	exit(EXIT_SUCCESS);
	
}
