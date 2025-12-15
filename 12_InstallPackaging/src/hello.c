#ifndef ENABLE_NLS
#define ENABLE_NLS 1
#endif

#include <libintl.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "strutil.h"

#define _(STR) gettext(STR)

#ifndef LOCALEDIR
#define LOCALEDIR "/usr/share/locale"
#endif

#ifndef TEXTDOMAIN
#define TEXTDOMAIN "greeter"
#endif

#ifndef BUILD_LOCALEDIR
#define BUILD_LOCALEDIR LOCALEDIR
#endif

int main(int argc, char **argv)
{
	char name[128];
	const char *progname = (argv && argv[0]) ? argv[0] : "greeter";

	for (int i = 1; i < argc; ++i)
	{
		if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0)
		{
			printf("Usage: %s [--help] [--version]\n", progname);
			return 0;
		}
		if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-V") == 0)
		{
			printf("greeter 1.0\n");
			return 0;
		}
	}

	setenv("LANG", "ru_RU.UTF-8", 1);
	setenv("LC_ALL", "ru_RU.UTF-8", 1);
	setenv("LC_MESSAGES", "ru_RU.UTF-8", 1);
	setenv("LANGUAGE", "ru", 1);
	if (setlocale(LC_ALL, "ru_RU.UTF-8") == NULL)
	{
		if (setlocale(LC_ALL, "en_US.UTF-8") == NULL)
		{
			if (setlocale(LC_ALL, "C.UTF-8") == NULL)
			{
				setlocale(LC_ALL, "");
			}
		}
	}

	const char *override_dir = getenv("GREETER_LOCALEDIR");
	const char *locale_dir = override_dir && *override_dir ? override_dir : LOCALEDIR;

	if (!override_dir && access(BUILD_LOCALEDIR "/ru/LC_MESSAGES/" TEXTDOMAIN ".mo", R_OK) == 0)
	{
		locale_dir = BUILD_LOCALEDIR;
	}

	bindtextdomain(TEXTDOMAIN, locale_dir);
	bind_textdomain_codeset(TEXTDOMAIN, "UTF-8");
	textdomain(TEXTDOMAIN);

	printf(_("Enter your name: "));
	if (fgets(name, sizeof(name), stdin) == NULL)
	{
		printf(_("Hello, stranger!\n"));
		return 0;
	}

	name[strcspn(name, "\n")] = '\0';

	if (name[0])
	{
		str_to_upper(name);
	}

	printf(_("Hello, %s!\n"), name[0] ? name : _("stranger"));
	return 0;
}
