#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include <sys/un.h>

typedef struct crcData{
	char msg[100];
	char divisor[20];
}crc;


void main(){
	remove("mySock");
	
	//creating server socket ss
	int ss= socket(AF_UNIX, SOCK_STREAM, 0);
	
	//binding server address to ss
	
	//defining structure to store address of server 
	struct sockaddr_un saddr, caddr;
	saddr.sun_family= AF_UNIX;
	strcpy(saddr.sun_path, "mySock");
	
	//binding
	bind(ss, (struct sockaddr *)&saddr, sizeof(saddr));
	
	//creating the listen queue
	listen(ss, 5);
	
	//accepting
	int length= sizeof(caddr);
	int ts= accept(ss, (struct sockaddr *)&caddr, &length);		//using *length since kernel needs to update the size in the original place
	
	
	//reading and writing of data
	
	while(1){
		//reading
		crc data;
		read(ts, (void *)&data, sizeof(data));
		printf("Message read from client\n");
		//printf("Message read: %s\n", data.msg);
		//printf("divisor read: %s\n", data.divisor);
		
		//processing
		if(strcmp(data.msg, "EXIT")==0 || strcmp(data.msg, "exit")==0)	//exit condition
			break;
		
		
		int divisor_len= strlen(data.divisor);
		int msg_c= divisor_len;
		    
		char temp_d[20]= "";
		strncat(temp_d, data.msg, divisor_len);
		
		char r[20]= "";
		    
	    	while(msg_c<=strlen(data.msg)){
			
			memset(r, 0, sizeof(r));
			//printf("temp_d: %s\n", temp_d);
			//doing xor
			
			for(int i=0; i<divisor_len; i++){
			        if(temp_d[i]==data.divisor[i])
				        r[i]= '0';
			        else
				        r[i]= '1';
			}
			//printf("r: %s\n", r);
			//removing starting zeroes from remainder and updating temp_d
			int pos=0;
			while(r[pos]=='0')
			        pos++;		

			int start=0;
			while(pos<divisor_len)
			    temp_d[start++]= r[pos++];
			
			
			//carrying bits from og msg if needed
			while(start<divisor_len)
			    temp_d[start++]= data.msg[msg_c++];
			    
		        //printf("new temp,msg_count: %s %d\n", temp_d,msg_c);
			
		    }
		    
                    //printf("r: %s\n", r);
		    //updating the msg for sending back to client
		    int i=strlen(data.msg)-1;
		    int j=strlen(temp_d)-1;
		    
		    //printf("i: %d\n", i);
		    for(;j>=0; i--, j--){
			data.msg[i]=temp_d[j];
				
		    }
		    //data.msg[i]='\0';
		    printf("Final message is: %s\n", data.msg);
		    
		    //sending data back to client
		    write(ts, (void *)&data, sizeof(data));
		    printf("Message sent to client\n\n");
		
		
		sleep(1);		
	}
	
	//closing the temp socket
	close(ts);
	//remove("mySock");
}
