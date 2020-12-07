#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <libc.h>

const char	*auth_str = "auth ";
const char	*reset_str = "reset";
const char	*service_str = "service";
const char	*login_str = "login";

int		main(void)
{
	static char	*auth;
	static char	*service;
	char		buf[0x80];		
	int			i;

	while (42)
	{
		auth_checker:
		printf("%p, %p \n", auth, service);
		if (!fgets(buf, 0x80, stdin))
			break ;
		i = 0;
		while (auth_str[i])
		{
			if (auth_str[i] != buf[i])
				goto reset_checker;
			i++;
		}
		auth = malloc(4);
		strcpy(auth, &buf[i]);

		reset_checker:
		i = 0;
		while (reset_str[i])
		{
			if (reset_str[i] != buf[i])
				goto service_checker;
			i++;
		}
		free(auth);

		service_checker:
		i = 0;
		while (service_str[i])
		{
			if (service_str[i] != buf[i])
				goto login_checker;
			i++;
		}
		service = strdup(&buf[i]);

		login_checker:
		i = 0;
		while (login_str[i])
		{
			if (login_str[i] != buf[i])
				goto auth_checker;
			i++;
		}
		if (auth[0x20])
			system("/bin/sh");
		else
			fwrite("Password:\n", 10, 1, stdout);
	}
	return (0);
}