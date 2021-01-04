/*
 * To show verbose and debug messages
 * G_MESSAGES_DEBUG=all ./ori ...
 * https://people.gnome.org/~ryanl/glib-docs/glib-Message-Logging.html
 * Will control better with another logging manager, probably my own g_log handler.
 *
 */

#include "cli_arguments.h"

#define G_LOG_DOMAIN    ((gchar*) 0)



void cli_arguments_parse(gchar **args) {
	GError *error = NULL;
	GOptionContext *context;


	static GOptionEntry cli_argument_options[] =
	{
		{"service_enable_dns", 0, 0, G_OPTION_ARG_NONE,
				&cli_argument_service_enable_dns, "Enable DNS Service", NULL},
	    {"service_enable_http", 0, 0, G_OPTION_ARG_NONE,
	    		&cli_argument_service_enable_http, "Enable HTTP Service", NULL},
	    {"service_enable_smtp", 0, 0, G_OPTION_ARG_NONE,
	    		&cli_argument_service_enable_smtp, "Enable SMTP Service", NULL},
		{"configuration_file", 'c', 0, G_OPTION_ARG_FILENAME,
				&cli_argument_configuration_file, "Configuration File", NULL},
		{NULL}
	};

	/* Defaults */
	if (!cli_argument_configuration_file) {
		cli_argument_configuration_file = "ori.ini";
	}


	context = g_option_context_new ("");
	g_option_context_set_summary (context, "Ori C2 - A WIP C2 program written by a @sogonsec");
	g_option_context_add_main_entries(context, cli_argument_options, NULL);
	if (!g_option_context_parse_strv(context, &args, &error)) {
		g_error("command line argument parsing failed: %s\n", error->message);
		exit (EXIT_FAILURE);
	}

	g_log_set_handler(G_LOG_DOMAIN, G_LOG_LEVEL_MASK, g_log_default_handler, NULL);

	if (cli_argument_service_enable_dns) {
		g_info("Enabling the DNS service.\n");
		g_debug("cli_argument_service_enable_dns is TRUE");
	}
	else {
		g_debug("cli_argument_service_enable_dns is FALSE");
	}
	if (cli_argument_service_enable_http) {
		g_info("Enabling the HTTP service.\n");
		g_debug("cli_argument_service_enable_http is TRUE");
	}
	else {
		g_debug("cli_argument_service_enable_http is FALSE");
	}
	if (cli_argument_service_enable_smtp) {
		g_info("Enabling the SMTP service.\n");
		g_debug("cli_argument_service_enable_smtp is TRUE");
	}
	else {
		g_debug("cli_argument_service_enable_smtp is FALSE");
	}
	g_debug("cli_argument_configuration_file = %s", cli_argument_configuration_file);
	g_info("Loading configuration from file '%s'.\n", cli_argument_configuration_file);

}
