#include "configuration.h"

Settings* load_configuration_file(gchar *filename) {
	Settings *conf;
	GKeyFile *keyfile;
	GKeyFileFlags flags;
	GError *error = NULL;
	gsize length;

	/* Create a new GKeyFile object and a bitwise list of flags. */
	keyfile = g_key_file_new();
	flags = G_KEY_FILE_KEEP_COMMENTS | G_KEY_FILE_KEEP_TRANSLATIONS;

	if (!g_key_file_load_from_file(keyfile, filename, flags, &error)) {
		g_error("Unable to load configuration from configuration file '%s': %s", filename, error->message);
		exit (EXIT_FAILURE);
	}

	conf = g_slice_new(Settings);

	conf->configuration_file = filename;
	conf->service_enable_dns = g_key_file_get_boolean(keyfile, "service",
			"enable_dns", NULL);
	conf->service_enable_http = g_key_file_get_boolean(keyfile, "service",
			"enable_http", NULL);
	conf->service_enable_smtp = g_key_file_get_boolean(keyfile, "service",
			"enable_smtp", NULL);
	g_debug("CONF service_enable_dns: %s", (conf->service_enable_dns?"TRUE":"FALSE"));
	g_debug("CONF service_enable_http: %s", (conf->service_enable_http?"TRUE":"FALSE"));
	g_debug("CONF service_enable_smtp: %s", (conf->service_enable_smtp?"TRUE":"FALSE"));

	return conf;
}

