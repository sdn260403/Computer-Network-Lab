#include "h2.h"

int main()
{
        int sid,cid,l,n;
        
        struct sockaddr_in saddr,caddr;
        sid=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
        
        saddr.sin_family=AF_INET;
        saddr.sin_addr.s_addr=inet_addr(ip);
        saddr.sin_port=htons(sport);
        
        bind(sid,(struct sockaddr *)&saddr,sizeof(saddr));
        
        listen(sid,5);
        
        l=sizeof(caddr);
        printf("Server established...\n\n");
        while(1)
        {
                char msg[32],temp[32];
                
                cid=accept(sid,(struct sockaddr *)&caddr,&l);
                if(cid)
                        printf("Connection established...\n\n");
                        
                n=read(cid,(void*)msg,32);  
                msg[n]=0;
                
                if(!strcmp(msg, "EXIT") || !strcmp(msg, "exit"))
		{
			printf("Signing Off...\n");
			break;
		}
		
                printf("Data Rec'vd\n");    
                //# parity bits
                int m=strlen(msg),p=0,b_c=0,tot;
                while(pow(2,p)<m+p+1)
                        p++;
                //printf("%d\n",p);
                
                // parity bits insertion
                tot=m+p;
                int ti=0;
                for(int i=0;i<tot;i++)
                {
                        if(ceil(log2(tot-i)) == floor(log2(tot-i)))
                        {
                                int parity = 0;
                                for (int j = 1; j <= m-1; j++) 
                                        if ((j >> ti) & 1) 
                                                parity ^=msg[j-1];
                                printf("%d %d\n",tot-i,parity);          
                                temp[i] = (parity==0 || parity==48)?'0':'1';
                                ti++;
                        }
                                
                        else
                                temp[i]=msg[b_c++];
                }
                temp[tot]=0;
                // parity bits updation
                printf("%s\n",temp);
                /*for (int i = 0; i < p; i++) 
                {
                        int parity = 0;
                        for (int j = 1; j <= m-1; j++) 
                        {
                                if ((j >> i) & 1) 
                                        parity ^= (int)msg[j-1];
            
                        }
                        printf("%d %d\n",tot-(1<<i),parity);
                        int d=tot-(1 << i)-1;
                        temp[d] = (parity==0)?'0':'1';
                }*/
                
                write(cid,(void*)temp,sizeof(msg));
                close(cid);
        }
        
        close(sid);
        return 0;
}
