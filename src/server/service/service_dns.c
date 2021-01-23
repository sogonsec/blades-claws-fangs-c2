/* https://www.ietf.org/rfc/rfc1035.txt */


#include "service_dns.h"


void
service_dns_debug_request(struct dns_request *request)
{
	g_debug("request->header->id = %i", request->header->id);
	g_debug("request->header->qr = %i", request->header->qr);
	g_debug("request->header->opcode = %i", request->header->opcode);
	g_debug("request->header->aa = %i", request->header->aa);
	g_debug("request->header->tc = %i", request->header->tc);
	g_debug("request->header->rd = %i", request->header->rd);
	g_debug("request->header->ra = %i", request->header->ra);
	g_debug("request->header->z = %i", request->header->z);
	g_debug("request->header->rcode = %i", request->header->rcode);
	g_debug("request->header->qdcount = %i", request->header->qdcount);
	g_debug("request->header->ancount = %i", request->header->ancount);
	g_debug("request->header->nscount = %i", request->header->nscount);
	g_debug("request->header->arcount = %i", request->header->arcount);

	for (int i = (request->header->qdcount - 1); i > -1; i--) {
		struct dns_question *question;
		question = g_array_index(request->questions, struct dns_question *, i);
		g_debug("question->qname->str  = %s (idx = %i)", question->qname->str, i);
		g_debug("question->qtype  = %i (idx = %i)", question->qtype, i);
		g_debug("question->qclass = %i (idx = %i)", question->qclass, i);
	}
}

void
service_dns_parse_request(char buffer[], struct dns_request *request)
{
	gint id, flags, qdcount, ancount, nscount, arcount;

	/* HEADER */
	id = (u_char) buffer[0] + (u_char) buffer[1];
	flags = (u_char) buffer[2] + (u_char) buffer[3];
	qdcount = (u_char) buffer[4] + (u_char) buffer[5];
	ancount = (u_char) buffer[6] + (u_char) buffer[7];
	nscount = (u_char) buffer[8] + (u_char) buffer[9];
	arcount = (u_char) buffer[10] + (u_char) buffer[11];

	request->header->id = id;
	request->header->qr = flags & header_mask_qr;
	request->header->opcode = flags & header_mask_opcode;
	request->header->aa = flags & header_mask_aa;
	request->header->tc = flags & header_mask_tc;
	request->header->rd = flags & header_mask_rd;
	request->header->ra = flags & header_mask_ra;

	request->header->z = 0;
	request->header->rcode = 0;
	request->header->qdcount = qdcount;
	request->header->ancount = ancount;
	request->header->nscount = nscount;
	request->header->arcount = arcount;


	/* QUESTIONS */
	gint buffer_count = 12;
	gint qname_chunk_size = (u_int) buffer[buffer_count];
	buffer_count++;
	for (int qdcount = request->header->qdcount; qdcount > 0; qdcount--) {
		struct dns_question *question = g_slice_new(struct dns_question);
		GString *qname = g_string_new(NULL);

		while (qname_chunk_size != 0) {
			for (int i = 0; i < qname_chunk_size; i++) {
				char c = (char)buffer[buffer_count];
				buffer_count++;
				qname = g_string_append_c(qname, c);
			}
			qname_chunk_size = (u_int) buffer[buffer_count];
			buffer_count++;
			if (qname_chunk_size != 0)
				g_string_append_c(qname, '.');
		}
		question->qname = qname;

		question->qtype = (u_char) buffer[buffer_count];
		buffer_count++;
		question->qtype += (u_char) buffer[buffer_count];
		buffer_count++;

		question->qclass = (u_char) buffer[buffer_count];
		buffer_count++;
		question->qclass += (u_char) buffer[buffer_count];
		buffer_count++;

		g_array_append_val(request->questions, question);
	}
}
void 
service_dns_process_request(struct dns_request *request)
{
	/* Iterate through each question */
	for (int i = (request->header->qdcount - 1); i > -1; i--) {
		struct dns_question *question;
		question = g_array_index(request->questions, struct dns_question *, i);

		if (question->qtype == DNS_QTYPE_A) {
			g_debug("A Request, expecting at least one IP for '%s'", question->qname->str);
		} else if (question->qtype == DNS_QTYPE_AAAA) {
			g_debug("AAAA Request, expecting at least one IPv6 for '%s'", question->qname->str);
		} else if (question->qtype == DNS_QTYPE_NS) {
			g_debug("NS Request, expecting at least one hostname or IP for '%s'", question->qname->str);
		} else if (question->qtype == DNS_QTYPE_MD) {
		} else if (question->qtype == DNS_QTYPE_MF) {
		} else if (question->qtype == DNS_QTYPE_CNAME) {
			g_debug("CNAME Request, expecting at least one hostname or IP for '%s'", question->qname->str);
		} else if (question->qtype == DNS_QTYPE_SOA) {
			g_debug("SOA Request for '%s', need to look this up how it works", question->qname->str);
		} else if (question->qtype == DNS_QTYPE_MB) {
		} else if (question->qtype == DNS_QTYPE_MG) {
		} else if (question->qtype == DNS_QTYPE_MR) {
		} else if (question->qtype == DNS_QTYPE_NULL) {
		} else if (question->qtype == DNS_QTYPE_WKS) {
		} else if (question->qtype == DNS_QTYPE_PTR) {
		} else if (question->qtype == DNS_QTYPE_HINFO) {
		} else if (question->qtype == DNS_QTYPE_MINFO) {
		} else if (question->qtype == DNS_QTYPE_MX) {
			g_debug("MX Request, expecting at least one hostname or IP for '%s'", question->qname->str);
		} else if (question->qtype == DNS_QTYPE_TXT) {
			g_debug("TXT Request for '%s', need to look this up how it works", question->qname->str);
		} else if (question->qtype == DNS_QTYPE_AXFR) {
			g_debug("AXFR Request for '%s', need to look this up how it works... It should be TCP only", question->qname->str);
		} else if (question->qtype == DNS_QTYPE_MAILB) {
		} else if (question->qtype == DNS_QTYPE_MAILA) {
		} else if (question->qtype == DNS_QTYPE_ALL) {
			g_debug("* Request for '%s', all the things?? need to look this up how it works", question->qname->str);
		} else {
			g_warning("No idea what type of QTYPE this is: %i", question->qtype);
		}
	}
}


void
service_dns_cb_conn_new(evutil_socket_t listener, short event, void *arg)
{
	/* Socket data structures */
	struct event_base *base = arg;
	struct sockaddr_in server_sin;
	socklen_t server_sz = sizeof(server_sin);
	char buffer[512] = {0};

	/* DNS Request data structures */
	struct dns_request *request = g_slice_new(struct dns_request);
	request->header = g_slice_new(struct dns_header);
	request->questions = g_array_new(FALSE, FALSE, sizeof(struct dns_question *));


	/* Read the request from the client, max 512 bytes for UDP */
	if (recvfrom(listener, &buffer, sizeof(buffer), 0,
	    (struct sockaddr *)&server_sin, &server_sz) == -1) {
		perror("recvfrom()");
		g_error("service_dns_callback_connection_new: recvfrom() failed");
		event_base_loopbreak(base);
	}
	/* Parse the request from a stream of bits to a usable data structure */
	service_dns_parse_request(buffer, request);
	service_dns_debug_request(request);

	/* Process the request data structure into a response data structure */
	service_dns_process_request(request);

	/* Process the response into a stream of bits to send back to the
	 * client */
	/* XXX - inject data in here */


	/* Send the response back to the client */
	/* if (sendto(sock, buf, sizeof(buf), 0, (struct sockaddr *)
	 * &server_sin, server_sz) == -1 ) { perror("sendto()");
	 * event_base_loopbreak(base); } */



	/* Cleanup */
	if (request->questions)
		g_array_free(request->questions, TRUE);
	if (request->header)
		g_slice_free(struct dns_header, request->header);
	if (request)
		g_slice_free(struct dns_request, request);

}
