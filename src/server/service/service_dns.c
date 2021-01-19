#include "service_dns.h"

void service_dns_callback_connection_new(evutil_socket_t listener, short event, void *arg)
{
    struct event_base *base = arg;
    struct sockaddr_in server_sin;
    socklen_t server_sz = sizeof(server_sin);
    DnsHeader *dns_header = g_slice_new(DnsHeader);
    char buffer[512] = {0};
    gint16 id, flags, qdcount, ancount, nscount, arcount;


    /* Read the header */
    /* https://www.ietf.org/rfc/rfc1035.txt */
    /*                                 1  1  1  1  1  1
     *   0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
     * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
     * |                      ID                       |
     * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
     * |QR|   Opcode  |AA|TC|RD|RA|   Z    |   RCODE   |
     * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
     * |                    QDCOUNT                    |
     * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
     * |                    ANCOUNT                    |
     * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
     * |                    NSCOUNT                    |
     * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
     * |                    ARCOUNT                    |
     * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+*/

    if (recvfrom(listener, &buffer, sizeof(buffer), 0, (struct sockaddr *)&server_sin, &server_sz) == -1)
    {
        perror("recvfrom()");
        g_error("service_dns_callback_connection_new: recvfrom() failed");
        event_base_loopbreak(base);
    }

    id = (u_char)buffer[0];
    id += (u_char)buffer[1];
    flags = (u_char)buffer[2];
    flags += (u_char)buffer[3];
    qdcount = (u_char)buffer[4];
    qdcount += (u_char)buffer[5];
    ancount = (u_char)buffer[6];
    ancount += (u_char)buffer[7];
    nscount = (u_char)buffer[8];
    nscount += (u_char)buffer[9];
    arcount = (u_char)buffer[10];
    arcount += (u_char)buffer[11];

    dns_header->id = id;
    dns_header->qr = flags & header_mask_qr;
    dns_header->opcode = flags & header_mask_opcode;
    dns_header->aa = flags & header_mask_aa;
    dns_header->tc = flags & header_mask_tc;
    dns_header->rd = flags & header_mask_rd;
    dns_header->ra = flags & header_mask_ra;

    dns_header->z = 0;
    dns_header->rcode = 0;
    dns_header->qdcount = qdcount;
    dns_header->ancount = ancount;
    dns_header->nscount = nscount;
    dns_header->arcount = arcount;

    g_debug("dns_header->id = %i", dns_header->id);
    g_debug("dns_header->qr = %i", dns_header->qr);
    g_debug("dns_header->opcode = %i", dns_header->opcode);
    g_debug("dns_header->aa = %i", dns_header->aa);
    g_debug("dns_header->tc = %i", dns_header->tc);
    g_debug("dns_header->rd = %i", dns_header->rd);
    g_debug("dns_header->ra = %i", dns_header->ra);
    g_debug("dns_header->z = %i", dns_header->z);
    g_debug("dns_header->rcode = %i", dns_header->rcode);
    g_debug("dns_header->qdcount = %i", dns_header->qdcount);
    g_debug("dns_header->ancount = %i", dns_header->ancount);
    g_debug("dns_header->nscount = %i", dns_header->nscount);
    g_debug("dns_header->arcount = %i", dns_header->arcount);

    /*printf("buffer in hex: ");
    for (int i = 0; i < 512; i++)
        printf("%02x ", buffer[i]);
    printf("\n");*/

    /* Send the data back to the client */
    /*if (sendto(sock, buf, sizeof(CLOCK_TV), 0, (struct sockaddr *) &server_sin, server_sz) == -1 ) {
		perror("sendto()");
		event_base_loopbreak(base);
	}*/

    g_slice_free(DnsHeader, dns_header);
}
