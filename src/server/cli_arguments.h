#ifndef SERVER_CLI_ARGUMENTS_H_
#define SERVER_CLI_ARGUMENTS_H_

#include <glib.h>
#include <glib/gi18n.h>

#include "configuration.h"

void cli_arguments_parse(gchar ** args, struct settings *conf);

#endif				/* SERVER_CLI_ARGUMENTS_H_ */
