#include <ctype.h>
#include <stddef.h>

#include "strutil.h"

/* str_to_upper - uppercase a NUL-terminated string in place; no-op on NULL. */
void str_to_upper(char *s)
{
	if (s == NULL)
	{
		return;
	}

	for (; *s; ++s)
	{
		*s = (char)toupper((unsigned char)*s);
	}
}
