#include "header.h"

int seqno=0,count=0,timeOut=0;
pthread_t t3;
sem_t s;

void* timer(void *arg)
{
        count+=1;
        printf("Started Timer%d\n",count);
        
        sleep(5);
        timeOut=1;
        sem_post(&s);
        pthread_exit(NULL);
}

void* sender(void *arg)
{
        int cid=*((int*)arg);
        while(1)
        {
                if(!timeOut)
                {
                        printf("Sending Frame%d \n",seqno);
                        write(cid,&seqno,sizeof(seqno));
                        seqno=(seqno+1)%2;
                }
                else
                {
                        seqno=(seqno+1)%2;
                        printf("Acknowledgement not received.Timer timed out.\nRe-Sending Frame%d \n",seqno);
                        write(cid,&seqno,sizeof(seqno));
                }
                timeOut=0;
                pthread_create(&t3,NULL,timer,NULL);
                sem_wait(&s);
                pthread_join(t3,NULL);               
        }
        pthread_exit(NULL);
}


void *receiver(void *arg)
{
        int cid=*((int*)arg);
        int ack;
        while(1)
        {
                read(cid,&ack,sizeof(ack));
                printf("Acknowledgement%d received. \n",seqno);
                if(ack==seqno)
                {
                        pthread_cancel(t3);
                        timeOut=0;
                        sem_post(&s);
                }              
        }
        pthread_exit(NULL); 
}
int main ()
{
    
    int cid = socket (AF_INET, SOCK_STREAM, 0);
    perror ("socket");

    struct sockaddr_in c;
    
    c.sin_family = AF_INET;
    c.sin_port = htons (5555);
    inet_aton ("127.0.0.1", &c.sin_addr);
    
    connect (cid, (struct sockaddr *) &c, sizeof (c));
    perror ("connect");

    
    sem_init(&s, 0, 1);
    pthread_t t1, t2;
    
    pthread_create (&t1, NULL, sender, (void *) &cid); 
    pthread_create (&t2, NULL, receiver, (void *) &cid);

    pthread_join (t1, NULL);
    pthread_join (t2, NULL);
    
    sem_destroy(&s);
    return 0;
}
