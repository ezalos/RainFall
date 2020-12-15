#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// char	*auth;
// char	*service;

int		main(void)
{
	static char	*auth;
	static char	*service;
	char		buf[0x80];

	while (42)
	{
		printf("%p, %p \n", auth, service);
		if (!fgets(buf, 0x80, stdin))
			break ;
		if (!strncmp(buf, "auth ", 5))
		{
			auth = malloc(4);
			((int*)auth)[0] = (int)0;
			if (strlen(buf + 5) <= 0x1e)
				strcpy(auth, buf + 5);
		}
		if (!strncmp(buf, "reset", 5))
			free(auth);
		if (!strncmp(buf, "service", 6))
			service = strdup(buf + 7);
		if (!strncmp(buf, "login", 5))
		{
			if (*(int*)(auth + 0x20))
				system("/bin/sh");
			else
				fwrite("Password:\n", 1, 10, stdout);
		}
	}
	return (0);
}

// gcc -fno-stack-protector source.c -o source  -z execstack
