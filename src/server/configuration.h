/**
 * https://developer.gnome.org/glib/stable/glib-Key-value-file-parser.html
 * http://www.gtkbook.com/gtkbook/keyfile.html
 *
 * All configuration file stuff
 */
#ifndef SERVER_CONFIGURATION_H_
#define SERVER_CONFIGURATION_H_

#include <glib.h>
#include <glib/gi18n.h>

struct settings {
	gchar *configuration_file;
	gboolean service_enable_dns;
	gboolean service_enable_http;
	gboolean service_enable_smtp;
};

struct settings *load_configuration_file(gchar * filename);

#endif				/* SERVER_CONFIGURATION_H_ */
