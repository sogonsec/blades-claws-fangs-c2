
#include "service.h"

ServiceData *service_generate(gint service_type, gint service_proto, gint port, struct event_base *base)
{
    ServiceData *service_data = g_slice_new(ServiceData);
    evutil_socket_t listener;
    struct sockaddr_in sin;
    struct event *listener_event;

    service_data->service_type = service_type;
    service_data->service_proto = service_proto;
    service_data->port = port;

    g_debug("service_type=%i", service_data->service_type);
    g_debug("service_proto=%i", service_data->service_proto);
    g_debug("port=%i", service_data->port);



    /* Create socket */
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(port);
    if (service_proto == SERVICE_PROTO_TCP)
    {
        listener = socket(AF_INET, SOCK_STREAM, 0);
    }
    else if (service_proto == SERVICE_PROTO_UDP)
    {
        listener = socket(AF_INET, SOCK_DGRAM, 0);
    }
    else
    {
        g_error("Unable to discern service proto '%i'", service_proto);
    }
    evutil_make_socket_nonblocking(listener);
    service_data->socket = listener;

#ifndef WIN32
    {
        int one = 1;
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    }
#endif
    /* Bind the socket */
    g_debug("Calling bind()");
    if (bind(listener, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        g_debug("bind() failed");
    }
    else {
        g_debug("bind() passed");
    }

    g_debug("Calling listen()");
    if (listen(listener, 16) < 0)
    {
        g_debug("listen() failed");
    }
    else {
        g_debug("listen() passed");
    }

    /* Register callbacks to libevent */
    if (service_data->service_type == SERVICE_TYPE_DNS)
    {
        g_debug("Adding listener for DNS");
        listener_event = event_new(base, listener, EV_READ | EV_PERSIST, service_dns_callback_connection_new, (void *)base);
    }
    else if (service_data->service_type == SERVICE_TYPE_SMTP)
    {
        g_debug("Adding listener for SMTP");
        listener_event = event_new(base, listener, EV_READ | EV_PERSIST, service_smtp_callback_connection_new, (void *)base);
    }
    else if (service_data->service_type == SERVICE_TYPE_HTTP)
    {
        g_debug("Adding listener for HTTP");
        listener_event = event_new(base, listener, EV_READ | EV_PERSIST, service_http_callback_connection_new, (void *)base);
    }
    else
    {
        g_error("Unable to discern service type");
    }
    g_debug("Adding listener event");
    event_add(listener_event, NULL);

    return (service_data);
}
