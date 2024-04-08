#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <math.h>
#include <string.h>
#include <pthread.h>

#define max 512
#define sip "127.0.0.1"
#define mip "224.0.0.1"
#define sport 1235
#define dport 1236
#define mport 1234 
#define N 3
