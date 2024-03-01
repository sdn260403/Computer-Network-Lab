#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#include<signal.h>

#define MAX 512

struct name
{
	long int np;
	char N[BUFSIZ];
};

struct roll
{
        long int rp;
        int r;
};

struct total
{
        long int ty;
        int tot;
};

