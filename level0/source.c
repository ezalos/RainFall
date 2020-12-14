// gcc source.c -fno-stack-protector -z execstack
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	char	*argv[2];
	uid_t	euid;
	gid_t	egid;

	(void)ac;
	if (atoi(av[1]) == 0x1a7)
	{
		argv[0] = strdup("/bin/sh");
		argv[1] = 0;
		egid = getegid();
		euid = geteuid();
		setresgid(egid, egid, egid);
		setresuid(euid, euid, euid);
		execv("/bin/sh", argv);
	}
	else
		fwrite("No !\n", 1, 5, stderr);
	return (0);
}
