
#ifndef SERVER_SERVICE_H_
#define SERVER_SERVICE_H_

#include <glib.h>
#include <glib/gi18n.h>
#include <event2/event.h>

#include "service_dns.h"
#include "service_http.h"
#include "service_smtp.h"

#define SERVICE_PROTO_TCP 1
#define SERVICE_PROTO_UDP 2
/*#define SERVICE_PROTO_UNIX  4*/

#define SERVICE_TYPE_DNS 1
#define SERVICE_TYPE_SMTP 2
#define SERVICE_TYPE_HTTP 4
/*#define SERVICE_TYPE_UNIX    8*/

struct service_data {
	gint service_proto;
	gint service_type;
	gint port;
	evutil_socket_t socket;
	struct sockaddr_in *sin;
};

struct service_data *service_generate(gint service_type, gint service_proto, gint port, struct event_base *base);

#endif				/* SERVER_SERVICE_H_ */
