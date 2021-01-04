#include <stdio.h>
#include <stdlib.h>

#include <glib.h>
#include <glib/gi18n.h>

gboolean	 cli_argument_service_enable_dns;
gboolean	 cli_argument_service_enable_http;
gboolean	 cli_argument_service_enable_smtp;
gchar		*cli_argument_configuration_file;

void cli_arguments_parse(gchar **args);
