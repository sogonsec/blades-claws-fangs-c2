#include "service_smtp.h"

void
service_smtp_callback_error(struct bufferevent *bev, short error, void *ctx)
{
	if (error & BEV_EVENT_EOF) {
		/* connection has been closed, do any clean up here */
		g_debug("service_smtp_callback_error: connection has been closed");
	} else if (error & BEV_EVENT_ERROR) {
		/* check errno to see what error occurred */
		g_debug("service_smtp_callback_error: some error: %s", strerror(error));
	} else if (error & BEV_EVENT_TIMEOUT) {
		/* must be a timeout event handle, handle it */
		g_debug("service_smtp_callback_error: timeout");
	}
	bufferevent_free(bev);
}
void
service_smtp_callback_read(struct bufferevent *bev, void *ctx)
{
	struct evbuffer *input, *output;
	char *line;
	size_t n;

	input = bufferevent_get_input(bev);
	output = bufferevent_get_output(bev);

	while ((line = evbuffer_readln(input, &n, EVBUFFER_EOL_LF))) {
		g_debug("service_smtp_callback_read; line=%s", line);
		evbuffer_add(output, line, n);
		evbuffer_add(output, "\n", 1);
		free(line);
	}

	if (evbuffer_get_length(input) >= MAX_LINE) {
		char buf[1024];
		while (evbuffer_get_length(input)) {
			int n = evbuffer_remove(input, buf, sizeof(buf));
			g_debug("service_smtp_callback_read; buf=%s", buf);

			evbuffer_add(output, buf, n);
		}
		evbuffer_add(output, "\n", 1);
	}
}

void
service_smtp_callback_connection_new(evutil_socket_t listener, short event, void *arg)
{
	struct event_base *base = arg;
	struct sockaddr_storage ss;
	socklen_t slen = sizeof(ss);
	int fd = accept(listener, (struct sockaddr *)&ss, &slen);
	if (fd < 0) {
		perror("accept");
	} else if (fd > FD_SETSIZE) {
		close(fd);
	} else {
		g_debug("service_smtp_callback_connection_new called");

		struct bufferevent *bev;
		evutil_make_socket_nonblocking(fd);
		bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
		bufferevent_setcb(bev, service_smtp_callback_read, NULL, service_smtp_callback_error, NULL);
		bufferevent_setwatermark(bev, EV_READ, 0, MAX_LINE);
		bufferevent_enable(bev, EV_READ | EV_WRITE);
	}
}
