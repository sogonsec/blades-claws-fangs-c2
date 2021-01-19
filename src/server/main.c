#define G_LOG_USE_STRUCTURED 1
#include <glib.h>
#include <glib/gi18n.h>

#include <netinet/in.h>
#include <sys/socket.h>

#include <fcntl.h>
#include <unistd.h>

#include <event2/event.h> /* http://www.wangafu.net/~nickm/libevent-book/01_intro.html */
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

int main(int argc, char **argv)
{
	gchar **cli_args;														 /* CLI arguments */
	Settings *conf;															 /* All settings */
	struct event_base *base;												 /* LibEvent */
	GArray *ServiceDatas = g_array_new(FALSE, FALSE, sizeof(ServiceData *)); /* Services */

	base = event_base_new();
	if (!base)
		g_error("event_base_new() failed");

	/*
	 * Read command line arguments
	 */

	cli_args = g_strdupv(argv);
	cli_arguments_parse(cli_args);
	g_strfreev(cli_args);

	/*
	 * Configuration file handling
	 */
	conf = load_configuration_file(cli_argument_configuration_file);

	/* CLI overrides */
	if (cli_argument_service_enable_dns && cli_argument_service_enable_dns != conf->service_enable_dns)
	{
		g_debug("CLI override for service_enable_dns");
		conf->service_enable_dns = cli_argument_service_enable_dns;
	}
	if (cli_argument_service_enable_http && cli_argument_service_enable_http != conf->service_enable_http)
	{
		g_debug("CLI override for service_enable_http");
		conf->service_enable_http = cli_argument_service_enable_http;
	}
	if (cli_argument_service_enable_smtp && cli_argument_service_enable_smtp != conf->service_enable_smtp)
	{
		g_debug("CLI override for service_enable_smtp");

		conf->service_enable_smtp = cli_argument_service_enable_smtp;
	}
	g_debug("FINAL configuration_file: %s", conf->configuration_file);
	g_debug("FINAL service_enable_dns: %s",
			(conf->service_enable_dns ? "TRUE" : "FALSE"));
	g_debug("FINAL service_enable_http: %s",
			(conf->service_enable_http ? "TRUE" : "FALSE"));
	g_debug("FINAL service_enable_smtp: %s",
			(conf->service_enable_smtp ? "TRUE" : "FALSE"));

	/*
	 * Service provisioning, setup, and registering.
	 * - Create sockets, register callbacks
	 */
	/* TODO: plugin hook */
	if (conf->service_enable_dns)
	{
		/* TODO: plugin hook */

		ServiceData *service_data_dns;
		service_data_dns = service_generate(SERVICE_TYPE_DNS, SERVICE_PROTO_UDP, 53, base);
		g_array_append_val(ServiceDatas, service_data_dns);

		/* TODO: plugin hook */
	}
	if (conf->service_enable_http)
	{
		/* TODO: plugin hook */

		ServiceData *service_data_http;
		service_data_http = service_generate(SERVICE_TYPE_HTTP, SERVICE_PROTO_TCP, 80, base);
		g_array_append_val(ServiceDatas, service_data_http);

		/* TODO: plugin hook */
	}
	if (conf->service_enable_smtp)
	{
		/* TODO: plugin hook */

		ServiceData *service_data_smtp;
		service_data_smtp = service_generate(SERVICE_TYPE_SMTP, SERVICE_PROTO_TCP, 25, base);
		g_array_append_val(ServiceDatas, service_data_smtp);

		/* TODO: plugin hook */
	}
	/* TODO: plugin_hook */

	/* TODO: plugin hook */
	event_base_dispatch(base);
	/* TODO: plugin hook */

	/* 
	 * Cleanup 
	 */
	/* XXX - Close all sockets */
	g_array_free(ServiceDatas, TRUE);

	return (EXIT_SUCCESS);
}
