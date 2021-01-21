#include "service_dns.h"

void
service_dns_cb_conn_new(evutil_socket_t listener, short event, void *arg)
{
	struct event_base *base = arg;
	struct sockaddr_in server_sin;
	socklen_t server_sz = sizeof(server_sin);
	struct dns_header *header = g_slice_new(struct dns_header);
	char buffer[512] = {0};
	gint16 id, flags, qdcount, ancount, nscount, arcount;

	/* Read the header */
	/* https://www.ietf.org/rfc/rfc1035.txt */

	if (recvfrom(listener, &buffer, sizeof(buffer), 0,
	    (struct sockaddr *)&server_sin, &server_sz) == -1) {
		perror("recvfrom()");
		g_error("service_dns_callback_connection_new: recvfrom() failed");
		event_base_loopbreak(base);
	}
	id = (u_char) buffer[0] + (u_char) buffer[1];
	flags = (u_char) buffer[2] + (u_char) buffer[3];
	qdcount = (u_char) buffer[4] + (u_char) buffer[5];
	ancount = (u_char) buffer[6] + (u_char) buffer[7];
	nscount = (u_char) buffer[8] + (u_char) buffer[9];
	arcount = (u_char) buffer[10] + (u_char) buffer[11];

	header->id = id;
	header->qr = flags & header_mask_qr;
	header->opcode = flags & header_mask_opcode;
	header->aa = flags & header_mask_aa;
	header->tc = flags & header_mask_tc;
	header->rd = flags & header_mask_rd;
	header->ra = flags & header_mask_ra;

	header->z = 0;
	header->rcode = 0;
	header->qdcount = qdcount;
	header->ancount = ancount;
	header->nscount = nscount;
	header->arcount = arcount;

	g_debug("header->id = %i", header->id);
	g_debug("header->qr = %i", header->qr);
	g_debug("header->opcode = %i", header->opcode);
	g_debug("header->aa = %i", header->aa);
	g_debug("header->tc = %i", header->tc);
	g_debug("header->rd = %i", header->rd);
	g_debug("header->ra = %i", header->ra);
	g_debug("header->z = %i", header->z);
	g_debug("header->rcode = %i", header->rcode);
	g_debug("header->qdcount = %i", header->qdcount);
	g_debug("header->ancount = %i", header->ancount);
	g_debug("header->nscount = %i", header->nscount);
	g_debug("header->arcount = %i", header->arcount);

	/* printf("buffer in hex: "); for (int i = 0; i < 512; i++)
	 * printf("%02x ", buffer[i]); printf("\n"); */

	/* Send the data back to the client */
	/* if (sendto(sock, buf, sizeof(CLOCK_TV), 0, (struct sockaddr *)
	 * &server_sin, server_sz) == -1 ) { perror("sendto()");
	 * event_base_loopbreak(base); } */

	g_slice_free(struct dns_header, header);
}
