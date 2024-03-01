#include "header.h"
int msgid,t,i,roll;
void handle(int signum)
{
        printf("\nSignal No.: %d\n",signum);
        msgctl(msgid,IPC_RMID,NULL);
        exit(0);
}
int main()
{
        signal(SIGINT,handle);
	
	struct name n,n1;
	struct roll rno,rno1;
	struct total t1,t2;
	char name[BUFSIZ];
	long int p=5,q=6;
	int l;
	
	key_t k=ftok("memory",67);
	msgid = msgget(k, 0666 | IPC_CREAT);
	if (msgid == -1) 
	{
		printf("msgid ERROR");
		exit(EXIT_FAILURE);
	}

	printf("Enter Number of students: ");
	scanf("%d",&t);
	
	t1.ty=3;
	t1.tot=t;
	msgsnd(msgid,(void *)&t1,512,0);
	
	t2.tot=t;
	t2.ty=4;
	msgsnd(msgid,(void *)&t2,512,0);
	
	printf("total number of students sent\n");
	
	for(i=0;i<t;i++)
	{
	        printf("Enter roll no. %d : ",i+1);
	        scanf("%d",&roll);
	        getchar();
	        printf("Enter length of name of %d : ",i+1);
	        scanf("%d",&l);
	        getchar();
	        printf("Enter name of %d : ",i+1);
	        fgets(name,l*sizeof(char),stdin);
	        getchar();
	        
	        
	        n.np=1;
	        rno.rp=2;
	        
	        strcpy(n.N,name);
	        rno.r=roll;
	
	        if(msgsnd(msgid,(void *)&n,BUFSIZ,0)==-1)
	        {
	                printf("Name cannot be sent in queue\n");
	                msgctl(msgid,IPC_RMID,0);
	                exit(1);
	        }
	        
	        if(msgsnd(msgid,(void *)&rno,BUFSIZ,0)==-1)
	        {
	                printf("Roll number cannot be sent in queue\n");
	                msgctl(msgid,IPC_RMID,0);
	                exit(1);
	        }
	        printf("Data of %d sent successfully\n",i+1);
	}
	sleep(1);
	printf("SORTED NAMES AND ROLL NUMBERS:\n");
	
	for(i=0;i<t;i++)
	{
	        if(msgrcv(msgid,(void *)&n1,BUFSIZ,p,0)==-1)
	        {
	                printf("Name Read error\n");
	                exit(1);
	        }
	        
	        if(msgrcv(msgid,(void *)&rno1,BUFSIZ,q,0)==-1)
	        {
	                printf("Roll Number Read error\n");
	                exit(1);
	        }
	        
	        printf("%s\t%d\n",n1.N,rno1.r);
	        
	}
	
	msgctl(msgid,IPC_RMID,NULL);
	exit(EXIT_SUCCESS);
	
}
