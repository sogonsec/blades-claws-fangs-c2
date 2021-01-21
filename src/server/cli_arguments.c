/*
 * To show verbose and debug messages
 * G_MESSAGES_DEBUG=all ./ogre_c2 ...
 * https://people.gnome.org/~ryanl/glib-docs/glib-Message-Logging.html
 * Will control better with another logging manager, probably my own g_log handler.
 *
 */

#include "cli_arguments.h"

void
cli_arguments_parse(gchar ** args, struct settings *conf)
{
	GError *error = NULL;
	GOptionContext *context;

	static gboolean cli_argument_service_enable_dns;
	static gboolean cli_argument_service_enable_http;
	static gboolean cli_argument_service_enable_smtp;
	static gchar *cli_argument_configuration_file;

	static GOptionEntry cli_argument_options[] =
	{
		{"service-enable-dns", 0, 0, G_OPTION_ARG_NONE,
		&cli_argument_service_enable_dns, "Enable DNS Service", NULL},
		{"service-enable-http", 0, 0, G_OPTION_ARG_NONE,
		&cli_argument_service_enable_http, "Enable HTTP Service", NULL},
		{"service-enable-smtp", 0, 0, G_OPTION_ARG_NONE,
		&cli_argument_service_enable_smtp, "Enable SMTP Service", NULL},
		{"configuration-file", 'c', 0, G_OPTION_ARG_FILENAME,
		&cli_argument_configuration_file, "Configuration File", NULL},
		{NULL}
	};

	/* Defaults */
	context = g_option_context_new("");
	g_option_context_set_summary(context, "Ogre C2 - A WIP C2 program written by a @sogonsec");
	g_option_context_add_main_entries(context, cli_argument_options, NULL);
	if (!g_option_context_parse_strv(context, &args, &error)) {
		g_error("command line argument parsing failed: %s\n", error->message);
		exit(EXIT_FAILURE);
	}
	if (cli_argument_service_enable_dns) {
		conf->service_enable_dns = 1;
	}
	if (cli_argument_service_enable_http) {
		conf->service_enable_http = 1;
	}
	if (cli_argument_service_enable_smtp) {
		conf->service_enable_smtp = 1;
	}
	if (cli_argument_configuration_file) {
		strlcpy(conf->configuration_file, cli_argument_configuration_file, sizeof(conf->configuration_file));
	}
}
