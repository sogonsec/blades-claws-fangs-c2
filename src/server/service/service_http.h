
#ifndef SERVER_SERVICE_HTTP_H_
#define SERVER_SERVICE_HTTP_H_

#include <glib.h>
#include <glib/gi18n.h>
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <unistd.h>

#define MAX_LINE 16384

void service_http_callback_connection_new(evutil_socket_t listener, short event, void *arg);
void service_http_callback_error(struct bufferevent *bev, short error, void *ctx);
void service_http_callback_read(struct bufferevent *bev, void *ctx);

#endif /* SERVER_SERVICE_HTTP_H_ */
