#include "h2.h"

int main()
{
        int sid,cid,l,n;
        char msg[32],temp[32];
        
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
                
                memset(msg, 0, sizeof(msg));
                memset(temp, 0, sizeof(temp));
                
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
                int m=strlen(msg),p=1,b_c=0,tot,shift=0,count=0;
                while(pow(2,p)<m+p+1)
                        p++;
                printf("%d Parity bits\n",p);
                
                // parity bits insertion
                tot=m+p;
                
                 for (int i = 0; i < m / 2; i++)
                 {
                        char t = msg[i];
                        msg[i] = msg[m - 1 - i];
                        msg[m - 1 - i] = t;
                 }           

               
                for(int i=0;i<tot;i++)
                {
                        if(!((i + 1) & i))
                                temp[i]='r';
                        else
                                temp[i]=msg[b_c++];
                }
                temp[tot]=0;
                printf("%s\n",temp);
                for(int i=0;i<p;i++)
                {
                        shift=1<<i;
                        count=0;
                        for (int j = 1; j <=tot; j++) 
                                if (j & shift )
                                        if(temp[j-1]=='1')
                                                count++;
                        printf("Count: %d\n",count);          
                        temp[shift - 1] = (count%2==0)?'0' :'1';                      
                }
                for (int i = 0; i < tot / 2; i++)
                 {
                        char t = temp[i];
                        temp[i] = temp[tot - 1 - i];
                        temp[tot - 1 - i] = t;
                 } 
                printf("%s\n",temp);
                
                
                write(cid,(void*)temp,sizeof(msg));
                close(cid);
        }
        
        close(sid);
        return 0;
}
