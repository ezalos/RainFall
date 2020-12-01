#include <stdio.h>
#include <stdlib.h>

void	run(void)
{
	fwrite("Good... Wait what?\n", 1, 19, stdout);
	system("/bin/sh");
}

void	main()
{
	char	buf[0x40];

	gets(buf);
}
