#define G_LOG_USE_STRUCTURED 1
#include <glib.h>
#include <glib/gi18n.h>

#include <netinet/in.h>
#include <sys/socket.h>

#include <fcntl.h>
#include <unistd.h>

#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>

#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "cli_arguments.h"
#include "configuration.h"
#include "service/service.h"

int
main(int argc, char **argv)
{
	gchar **cli_args;	/* CLI arguments */
	struct settings *conf = g_slice_new(struct settings);	/* All settings */
	struct event_base *base;/* LibEvent */
	GArray *ServiceDatas = g_array_new(FALSE, FALSE, sizeof(struct server_data *));	/* Services */

	/* Init glib */
	g_log_set_handler(G_LOG_DOMAIN, G_LOG_LEVEL_MASK, g_log_default_handler, NULL);

	/* Init libevent */
	base = event_base_new();
	if (!base)
		g_error("event_base_new() failed");

	/* Init configuration */
	conf->configuration_file = "ogre.ini";
	conf->service_enable_dns = SERVICE_STATUS_UNKNOWN;
	conf->service_enable_http = SERVICE_STATUS_UNKNOWN;
	conf->service_enable_smtp = SERVICE_STATUS_UNKNOWN;

	/* Read command line arguments */
	cli_args = g_strdupv(argv);
	cli_arguments_parse(cli_args, conf);
	g_strfreev(cli_args);

	/* Configuration file handling */
	load_configuration_file(conf);


	/* Service provisioning, setup, and registering. - Create sockets,
	 * register callbacks */
	/* TODO: plugin hook */
	if (conf->service_enable_dns == SERVICE_STATUS_ENABLED) {
		/* TODO: plugin hook */

		struct service_data *service_data_dns;
		service_data_dns = service_generate(SERVICE_TYPE_DNS, SERVICE_PROTO_UDP, 53, base);
		g_array_append_val(ServiceDatas, service_data_dns);
		g_info("Service DNS Loaded");

		/* TODO: plugin hook */
	}
	if (conf->service_enable_http == SERVICE_STATUS_ENABLED) {
		/* TODO: plugin hook */

		struct service_data *service_data_http;
		service_data_http = service_generate(SERVICE_TYPE_HTTP, SERVICE_PROTO_TCP, 80, base);
		g_array_append_val(ServiceDatas, service_data_http);
		g_info("Service HTTP Loaded");

		/* TODO: plugin hook */
	}
	if (conf->service_enable_smtp == SERVICE_STATUS_ENABLED) {
		/* TODO: plugin hook */

		struct service_data *service_data_smtp;
		service_data_smtp = service_generate(SERVICE_TYPE_SMTP, SERVICE_PROTO_TCP, 25, base);
		g_array_append_val(ServiceDatas, service_data_smtp);
		g_info("Service SMTP Loaded");

		/* TODO: plugin hook */
	}
	/* TODO: plugin_hook */

	/* TODO: plugin hook */
	event_base_dispatch(base);
	/* TODO: plugin hook */

	/* Cleanup */
	/* XXX - Close all sockets */
	if (conf)
		g_slice_free(struct settings, conf);
	if (ServiceDatas)
		g_array_free(ServiceDatas, TRUE);

	return (EXIT_SUCCESS);
}
