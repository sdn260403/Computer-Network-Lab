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
#include <semaphore.h>

#define max 512
#define sip "127.0.0.1"
#define cip "127.0.0.1"
#define mip "224.0.0.1"
#define sport 1234
#define dport 1235
#define N 3
