// gcc -fno-stack-protector source.c -o source  -z execstack
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int	language;

int	greetuser(char *name)
{
	char	buf[0x40];

	switch (language)
	{
		case 1: goto finnish;
		case 2: goto dutch;
		case 0: break ;
		default: goto end;
	}
	strcpy(buf, "Hello ");
	goto end;
	finnish:
	strcpy(buf, "Hyvää päivää ");
	goto end;
	dutch:
	strcpy(buf, "Goedemiddag! ");
	end:
	return (puts(strcat(buf, name)));
}

int		main(int ac, char **av)
{
	char		*lang;

	if (ac != 3)
		return (1);
	char		buf[0x4c];
	char		tmp[0x40];
	memset(buf, '\0', 0x4c);
	strncpy(buf, av[1], 0x28);
	strncpy(buf + 0x28, av[2], 0x20);
	if ((lang = getenv("LANG")))
	{
		if (!memcmp(lang, "fi", 0x2))
			language = 1;
		else if (!memcmp(lang, "nl", 0x2))
			language = 2;
	}
	return (greetuser(buf));
}
