#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

struct udp_header {
	unsigned short int sprt;
	unsigned short int dprt;
	unsigned short int len;
	unsigned short int csum;
};

#define OPT_ICMP (1)
#define OPT_UDP (2)
#define OPT_TCP (4)

int send_icmp(struct in_addr inaddr);
int send_udp(struct sockaddr_in *sin, struct sockaddr_in *din, const char *data);
int send_tcp(struct in_addr inaddr);
