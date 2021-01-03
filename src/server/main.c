#include <stdio.h>
#include <stdlib.h>

#include <glib.h>
#include <glib/gi18n.h>

#include "cli_arguments.h"


int
main (int argc, char **argv) {
	gchar **args; /* CLI arguments */

	/*
	 * Read command line arguments
	 * https://developer.gnome.org/glib/2.32/glib-Commandline-option-parser.html
	 */
#ifdef G_OS_WIN32
	args = g_win32_get_command_line ();
#else
	args = g_strdupv (argv);
#endif

	cli_arguments_parse(args);
	g_strfreev (args);


	/*
	 * Create sockets
	 */

	/*
	 * Add sockets to event queue
	 */
}
