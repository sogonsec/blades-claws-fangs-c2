
#include "cli_arguments.h"

static gboolean	cli_argument_service_enable_dns	= FALSE;
static gboolean	cli_argument_service_enable_http	= FALSE;
static gboolean	cli_argument_service_enable_smtp	= FALSE;
static gchar	*cli_argument_configuration_file	= "config.ini";

static GOptionEntry cli_argument_options[] =
{
    {"service_enable_dns", 0, 0, G_OPTION_ARG_NONE, &cli_argument_service_enable_dns, "Enable DNS Service", NULL},
    {"service_enable_http", 0, 0, G_OPTION_ARG_NONE, &cli_argument_service_enable_http, "Enable HTTP Service", NULL},
    {"service_enable_smtp", 0, 0, G_OPTION_ARG_NONE, &cli_argument_service_enable_smtp, "Enable SMTP Service", NULL},
	{"configuration_file", 'c', 0, G_OPTION_ARG_FILENAME, &cli_argument_configuration_file, "Configuration File", NULL},
	{NULL}
};



void cli_arguments_parse(gchar **args) {

	GError *error = NULL;
	GOptionContext *context;

	context = g_option_context_new ("");
	g_option_context_add_main_entries (context, cli_argument_options, NULL);
	if (!g_option_context_parse_strv (context, &args, &error)) {
		g_print ("option parsing failed: %s\n", error->message);
		exit (EXIT_FAILURE);
	}

	if (cli_argument_service_enable_dns) {
		g_print("cli_argument_service_enable_dns is TRUE\n");
	}
	else {
		g_print("cli_argument_service_enable_dns is FALSE\n");
	}
	if (cli_argument_service_enable_http) {
		g_print("cli_argument_service_enable_http is TRUE\n");
	}
	else {
		g_print("cli_argument_service_enable_http is FALSE\n");
	}
	if (cli_argument_service_enable_smtp) {
		g_print("cli_argument_service_enable_smtp is TRUE\n");
	}
	else {
		g_print("cli_argument_service_enable_smtp is FALSE\n");
	}
	g_print("cli_argument_configuration_file = %s\n", cli_argument_configuration_file);
}
