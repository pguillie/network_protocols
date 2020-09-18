#include "network_protocols.h"

int send_udp(struct sockaddr_in *sin, struct sockaddr_in *din, const char *data)
{
	int sock;
	char buff[128];
	struct udp_header *udp = (void*)&buff;

	printf("Sending UDP packet to %s:%hu... ", inet_ntoa(din->sin_addr),
		ntohs(din->sin_port));
	sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	if (sock == -1) {
		perror("UDP socket");
		exit(1);
	}
	if (sin) {
		udp->sprt = sin->sin_port;
		/* spoof IP source address */
	}
	udp->dprt = din->sin_port;
	udp->len = htons(sizeof(*udp) + strlen(data));
	udp->csum = htons(0);
	strcpy(buff + sizeof(*udp), data);
	sendto(sock, buff, ntohs(udp->len), 0, (const struct sockaddr*)din, sizeof(*din));
	close(sock);
	puts("OK");
	return 0;
}
