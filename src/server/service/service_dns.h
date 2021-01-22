
#ifndef SERVER_SERVICE_DNS_H_
#define SERVER_SERVICE_DNS_H_

#include <glib.h>
#include <glib/gi18n.h>
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <unistd.h>

struct dns_request {
	/* HEADER */
	gint id;
	gint qr;
	gint opcode;
	gint aa;
	gint tc;
	gint rd;
	gint ra;
	gint z;
	gint rcode;
	gint qdcount;
	gint ancount;
	gint nscount;
	gint arcount;

	/* QUESTION */
	gchar *qname;
	gint qtype;
	gint qclass;
};
/*--Domain QTYPE----------------------------------------------------------
A               1 a host address
NS              2 an authoritative name server
MD              3 a mail destination (Obsolete - use MX)
MF              4 a mail forwarder (Obsolete - use MX)
CNAME           5 the canonical name for an alias
SOA             6 marks the start of a zone of authority
MB              7 a mailbox domain name (EXPERIMENTAL)
MG              8 a mail group member (EXPERIMENTAL)
MR              9 a mail rename domain name (EXPERIMENTAL)
NULL            10 a null RR (EXPERIMENTAL)
WKS             11 a well known service description
PTR             12 a domain name pointer
HINFO           13 host information
MINFO           14 mailbox or mail list information
MX              15 mail exchange
TXT             16 text strings
AXFR            252 A request for a transfer of an entire zone
MAILB           253 A request for mailbox-related records (MB, MG or MR)
MAILA           254 A request for mail agent RRs (Obsolete - see MX)
*               255 A request for all records
------------------------------------------------------------------------*/

static const uint header_mask_qr = 0x8000;
static const uint header_mask_opcode = 0x7800;
static const uint header_mask_aa = 0x0400;
static const uint header_mask_tc = 0x0200;
static const uint header_mask_rd = 0x0100;
static const uint header_mask_ra = 0x8000;
static const uint header_mask_rcode = 0x000F;

void service_dns_cb_conn_new(evutil_socket_t listener, short event, void *arg);

#endif				/* SERVER_SERVICE_DNS_H_ */
