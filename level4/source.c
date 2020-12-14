#include <stdio.h>
#include <stdlib.h>

void	p(char *buf)
{
	printf(buf);
}

void	n(void)
{
	char	buf[0x200];
	static int	m;

	fgets(buf, 0x200, stdin);
	p(buf);
	if (m == 0x1025544)
		system("/bin/cat /home/user/level5/.pass");
}

void	main(void)
{
	n();
}

// gcc -fno-stack-protector source.c -o source  -z execstack
