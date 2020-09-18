#include "network_protocols.h"

static void usage(const char *bin)
{
	fprintf(stderr, "Usage: %s [-iut] [src_addr [port]] dst_addr [port] [payload]\n", bin);
}

int main(int argc, char *argv[])
{
	char **ap;
	struct sockaddr_in addr[2], *addr1 = NULL, *addr2 = NULL;
	char protocols = OPT_ICMP | OPT_UDP | OPT_TCP;
	char *payload = NULL;

	if (argc < 2) {
		usage(argv[0]);
		return 1;
	}
	ap = argv + 1;
	if (*ap[0] == '-') {
		protocols = 0;
		for (char *c = *ap + 1; *c; c++) {
			switch (*c) {
			case 'i': protocols |= OPT_ICMP; break;
			case 'u': protocols |= OPT_UDP; break;
			case 't': protocols |= OPT_TCP; break;
			default: fprintf(stderr, "error: -%c: invalid option\n", *c);
				usage(argv[0]); return 1;
			}
		}
		ap++;
	}
	if (!*ap || !inet_aton(*ap, &addr[0].sin_addr)) {
		fprintf(stderr, "error: missing or invalid address\n");
		usage(argv[0]);
		return 1;
	} else {
		addr1 = &addr[0];
		addr1->sin_family = AF_INET;
		addr1->sin_port = htons(0);
		if (*++ap) {
			char *d;
			for (d = *ap; *d; d++)
				if (!isdigit(*d)) break;
			if (!*d) {
				int p = atoi(*ap);
				if (p >= 0 && p <= USHRT_MAX) {
					addr1->sin_port = htons(p);
					ap++;
				}
			}
		}
	}
	if (*ap && inet_aton(*ap, &addr[1].sin_addr)) {
		addr2 = &addr[1];
		addr2->sin_family = AF_INET;
		addr2->sin_port = htons(0);
		if (*++ap) {
			char *d;
			for (d = *ap; *d; d++)
				if (!isdigit(*d)) break;
			if (!*d) {
				int p = atoi(*ap);
				if (p >= 0 && p <= USHRT_MAX) {
					addr2->sin_port = htons(p);
					ap++;
				}
			}
		}
	}
	if (*ap) {
		if (*(ap + 1)) {
			usage(argv[0]);
			return 1;
		}
		payload = *ap++;
	}

	/* if (protocols & OPT_ICMP) */
	/* 	send_icmp(inaddr); */
	/* if (protocols & OPT_UPD) */
	send_udp(addr2 ? addr1 : NULL, addr2 ? addr2 : addr1, payload ? payload : "");
	/* if (protocols & OPT_TCP) */
	/* 	send_tcp(inaddr); */
	return 0;
}
