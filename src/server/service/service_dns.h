
#ifndef SERVER_SERVICE_DNS_H_
#define SERVER_SERVICE_DNS_H_

#include <glib.h>
#include <glib/gi18n.h>
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <unistd.h>

typedef struct
{
    gint id; /* 16 bits */

    gint qr;     /* 1 bit */
    gint opcode; /* 4 bits */
    gint aa;     /* 1 bit */
    gint tc;     /* 1 bit */
    gint rd;     /* 1 bit */
    gint ra;     /* 1 bit */
    gint z;      /* 3 bits */
    gint rcode;  /* 4 bits */

    gint qdcount; /* 16 bits */
    gint ancount; /* 16 bits */
    gint nscount; /* 16 bits */
    gint arcount; /* 16 bits */
} DnsHeader;

static const uint header_mask_qr = 0x8000;
static const uint header_mask_opcode = 0x7800;
static const uint header_mask_aa = 0x0400;
static const uint header_mask_tc = 0x0200;
static const uint header_mask_rd = 0x0100;
static const uint header_mask_ra = 0x8000;
static const uint header_mask_rcode = 0x000F;

void service_dns_callback_connection_new(evutil_socket_t listener, short event, void *arg);

#endif /* SERVER_SERVICE_DNS_H_ */
