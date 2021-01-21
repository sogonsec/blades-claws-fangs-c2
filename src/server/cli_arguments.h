#ifndef SERVER_CLI_ARGUMENTS_H_
#define SERVER_CLI_ARGUMENTS_H_

#include <glib.h>
#include <glib/gi18n.h>

gboolean cli_argument_service_enable_dns;
gboolean cli_argument_service_enable_http;
gboolean cli_argument_service_enable_smtp;
gchar *cli_argument_configuration_file;

void cli_arguments_parse(gchar ** args);

#endif				/* SERVER_CLI_ARGUMENTS_H_ */
