#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void	p(void)
{
	char	buf[0x40];
	void	*former_eip;

	fflush(stdout);
	gets(buf);
	former_eip =  __builtin_return_address(0);
	if (((unsigned int)former_eip & 0xb0000000) == 0xb0000000)
	{
		printf("(%p)\n", former_eip);
		_exit(1);
	}
	puts(buf);
	strdup(buf);
}

void 	main(void)
{
	p();
}

// gcc -fno-stack-protector source.c -o source  -z execstack
