
#ifndef SERVER_SERVICE_DNS_H_
#define SERVER_SERVICE_DNS_H_

#include <glib.h>
#include <glib/gi18n.h>
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <unistd.h>

struct dns_header {
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
};

struct dns_question {
	GString *qname;
	gint qtype;
	gint qclass;
};

struct dns_request {
	struct dns_header *header;
	GArray *questions;	/* contains dns_question structs */
};


#define DNS_QTYPE_A 1		/* a host address */
#define DNS_QTYPE_NS 2		/* an authoritative name server */
#define DNS_QTYPE_MD 3		/* a mail destination (Obsolete - use MX) */
#define DNS_QTYPE_MF 4		/* a mail forwarder (Obsolete - use MX) */
#define DNS_QTYPE_CNAME 5	/* the canonical name for an alias */
#define DNS_QTYPE_SOA 6		/* marks the start of a zone of authority */
#define DNS_QTYPE_MB 7		/* a mailbox domain name (EXPERIMENTAL) */
#define DNS_QTYPE_MG 8		/* a mail group member (EXPERIMENTAL) */
#define DNS_QTYPE_MR 9		/* a mail rename domain name (EXPERIMENTAL) */
#define DNS_QTYPE_NULL 10	/* a null RR (EXPERIMENTAL) */
#define DNS_QTYPE_WKS 11	/* a well known service description */
#define DNS_QTYPE_PTR 12	/* a domain name pointer */
#define DNS_QTYPE_HINFO 13	/* host information */
#define DNS_QTYPE_MINFO 14	/* mailbox or mail list information */
#define DNS_QTYPE_MX 15		/* mail exchange */
#define DNS_QTYPE_TXT 16	/* text strings */
#define DNS_QTYPE_AAAA 28   /* AAAA host record */
#define DNS_QTYPE_AXFR 252	/* A request for a transfer of an entire zone */
#define DNS_QTYPE_MAILB 253	/* A request for mailbox-related records (MB, MG or MR) */
#define DNS_QTYPE_MAILA 254	/* A request for mail agent RRs (Obsolete - see MX) */
#define DNS_QTYPE_ALL 255	/* A request for all records */

/* RFC 1035, section 4.1.1 */
static const guint header_mask_qr     = 0x8000; /* 1000 0000 0000 0000 */
static const guint header_mask_opcode = 0x7800; /* 0111 1000 0000 0000 */
static const guint header_mask_aa     = 0x0400; /* 0000 0100 0000 0000 */
static const guint header_mask_tc     = 0x0200; /* 0000 0010 0000 0000 */
static const guint header_mask_rd     = 0x0100; /* 0000 0001 0000 0000 */
static const guint header_mask_ra     = 0x0080; /* 0000 0000 1000 0000 */
static const guint header_mask_z      = 0x0070; /* 0000 0000 0111 0000 */
static const guint header_mask_rcode  = 0x000F; /* 0000 0000 0000 1111 */

void service_dns_cb_conn_new(evutil_socket_t listener, short event, void *arg);
void service_dns_debug_request(struct dns_request *request);
void service_dns_parse_request(char buffer[], struct dns_request *request);
void service_dns_process_request(struct dns_request *request);

#endif				/* SERVER_SERVICE_DNS_H_ */
