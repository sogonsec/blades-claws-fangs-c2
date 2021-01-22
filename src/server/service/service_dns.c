#include "service_dns.h"

void
service_dns_cb_conn_new(evutil_socket_t listener, short event, void *arg)
{
	struct event_base *base = arg;
	struct sockaddr_in server_sin;
	socklen_t server_sz = sizeof(server_sin);
	struct dns_request *request = g_slice_new(struct dns_request);
	char buffer[512] = {0};
	gint16 id, flags, qdcount, ancount, nscount, arcount;

	/* Read the request */
	/* https://www.ietf.org/rfc/rfc1035.txt */

	if (recvfrom(listener, &buffer, sizeof(buffer), 0,
	    (struct sockaddr *)&server_sin, &server_sz) == -1) {
		perror("recvfrom()");
		g_error("service_dns_callback_connection_new: recvfrom() failed");
		event_base_loopbreak(base);
	}

	/* HEADER */
	id = (u_char) buffer[0] + (u_char) buffer[1];
	flags = (u_char) buffer[2] + (u_char) buffer[3];
	qdcount = (u_char) buffer[4] + (u_char) buffer[5];
	ancount = (u_char) buffer[6] + (u_char) buffer[7];
	nscount = (u_char) buffer[8] + (u_char) buffer[9];
	arcount = (u_char) buffer[10] + (u_char) buffer[11];

	request->id = id;
	request->qr = flags & header_mask_qr;
	request->opcode = flags & header_mask_opcode;
	request->aa = flags & header_mask_aa;
	request->tc = flags & header_mask_tc;
	request->rd = flags & header_mask_rd;
	request->ra = flags & header_mask_ra;

	request->z = 0;
	request->rcode = 0;
	request->qdcount = qdcount;
	request->ancount = ancount;
	request->nscount = nscount;
	request->arcount = arcount;

	g_debug("request->id = %i", request->id);
	g_debug("request->qr = %i", request->qr);
	g_debug("request->opcode = %i", request->opcode);
	g_debug("request->aa = %i", request->aa);
	g_debug("request->tc = %i", request->tc);
	g_debug("request->rd = %i", request->rd);
	g_debug("request->ra = %i", request->ra);
	g_debug("request->z = %i", request->z);
	g_debug("request->rcode = %i", request->rcode);
	g_debug("request->qdcount = %i", request->qdcount);
	g_debug("request->ancount = %i", request->ancount);
	g_debug("request->nscount = %i", request->nscount);
	g_debug("request->arcount = %i", request->arcount);



	/* QUESTION */
	gint buffer_count = 12;
	gint qname_chunk_size = (u_int) buffer[buffer_count];
	buffer_count++;
	GString *qname = g_string_new(NULL);
    while (qname_chunk_size != 0) {
        for (int i = 0; i < qname_chunk_size; i++) {
            char c = (char) buffer[buffer_count];
			buffer_count++;
			qname = g_string_append_c(qname, c);
        }
        qname_chunk_size = (u_int) buffer[buffer_count];
		buffer_count++;
        if (qname_chunk_size != 0) 
			g_string_append_c(qname, '.');
    }
	request->qname = qname->str;

	request->qtype = (u_char) buffer[buffer_count];
	buffer_count++;
	request->qtype += (u_char) buffer[buffer_count];
	buffer_count++;

	request->qclass = (u_char) buffer[buffer_count];
	buffer_count++;
	request->qclass += (u_char) buffer[buffer_count];
	buffer_count++;

	g_debug("request->qname  = %s", request->qname);
	g_debug("request->qtype  = %i", request->qtype);
	g_debug("request->qclass = %i", request->qclass);



	/*printf("remaining buffer in hex: "); 
	for (int i = buffer_count; i < 512; i++)
	 	printf("%02x ", buffer[i]); 
	printf("\n");*/

	/* Send the data back to the client */
	/* if (sendto(sock, buf, sizeof(CLOCK_TV), 0, (struct sockaddr *)
	 * &server_sin, server_sz) == -1 ) { perror("sendto()");
	 * event_base_loopbreak(base); } */

	if (qname) 
		g_string_free(qname, TRUE);
	if (request)
		g_slice_free(struct dns_request, request);
}
