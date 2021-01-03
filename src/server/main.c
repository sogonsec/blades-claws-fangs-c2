#include <stdio.h>
#include <stdlib.h>

#define G_LOG_USE_STRUCTURED 1

#include <glib.h>
#include <glib/gi18n.h>

#include "cli_arguments.h"


int
main (int argc, char **argv) {
	gchar **cli_args; /* CLI arguments */

	/*
	 * Read command line arguments
	 * https://developer.gnome.org/glib/2.32/glib-Commandline-option-parser.html
	 */
#ifdef G_OS_WIN32
	cli_args = g_win32_get_command_line ();
#else
	cli_args = g_strdupv (argv);
#endif

	cli_arguments_parse(cli_args);
	g_strfreev (cli_args);

	/*
	 * Configuration file handling
	 */


	/*
	 * Create sockets
	 */

	/*
	 * Add sockets to event queue
	 */
}
