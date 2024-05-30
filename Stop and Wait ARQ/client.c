#include "header.h"

int main()
{
         struct sockaddr_in s, c;
        int r, ack = 0, seed = 10001000, delay;
    // Create socket
        int sid = socket (AF_INET, SOCK_STREAM, 0);
        perror ("socket");

    // Set socket address attributes
        s.sin_family = AF_INET;
        s.sin_port = htons (5555);
        inet_aton ("127.0.0.1", &s.sin_addr);
    // Bind socket
         bind (sid, (struct sockaddr *) &s, sizeof (s));
         perror ("bind");

    // Listen for incoming connections
        listen (sid, 1);
        perror ("listen");

    // Accept incoming connection
        int l = sizeof (c);
        int cid = accept (sid, (struct sockaddr *) &c, &l);
        perror ("accept");
        
        srand(seed);
        while(1)
        {
                read(cid,&r,sizeof(r));
                if(r==ack)
                {
                        printf("Acknowledgement%d received. \n",r);
                        ack=(ack+1)%2;
                }
                else 
                        printf("Received Duplicate Frame:%d \n",r);
                        
                delay=(rand()%10)+1;
                sleep(delay);
                
                write(cid,&ack,sizeof(ack));
                printf("Sending Ack%d.\n",ack);
                
        }
        return 0;
}
