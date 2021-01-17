#define G_LOG_USE_STRUCTURED 1
#include <glib.h>
#include <glib/gi18n.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <fcntl.h>

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
#include "service/dns/dns.h"
#include "service/http/http.h"
#include "service/smtp/smtp.h"

int main(int argc, char **argv) {
	gchar **cli_args; /* CLI arguments */
	Settings *conf; /* All settings */
	struct event_base *base; 

	base = event_base_new();
	if (!base)
	  g_error("event_base_new() failed");
       
	/*
	 * Read command line arguments
	 */
#ifdef G_OS_WIN32
	cli_args = g_win32_get_command_line();
#else
	cli_args = g_strdupv(argv);
#endif

	cli_arguments_parse(cli_args);
	g_strfreev(cli_args);

	/*
	 * Configuration file handling
	 */
	conf = load_configuration_file(cli_argument_configuration_file);

	/* CLI overrides */
	if (cli_argument_service_enable_dns
			&& cli_argument_service_enable_dns != conf->service_enable_dns) {
		g_debug("CLI override for service_enable_dns");
		conf->service_enable_dns = cli_argument_service_enable_dns;
	}
	if (cli_argument_service_enable_http
			&& cli_argument_service_enable_http != conf->service_enable_http) {
		g_debug("CLI override for service_enable_http");
		conf->service_enable_http = cli_argument_service_enable_http;
	}
	if (cli_argument_service_enable_smtp
			&& cli_argument_service_enable_smtp != conf->service_enable_smtp) {
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
	 * Create sockets, register callbacks
	 */
	/* TODO: plugin hook */
	if (conf->service_enable_dns) {
	  /* TODO: plugin hook */
	  
	  
	  /* Create socket */
	  /* Create service */
	  /* Register service */
	  
	  /* TODO: plugin hook */
	}
	if (conf->service_enable_http) {
	  /* TODO: plugin hook */
	  /* TODO: plugin hook */	  
	}
	if (conf->service_enable_smtp) {
	  /* TODO: plugin hook */
	  /* TODO: plugin hook */	  
	}
	/* TODO: plugin_hook */


	/* TODO: plugin hook */
	event_base_dispatch(base);
	/* TODO: plugin hook */
	return (EXIT_SUCCESS);
}
