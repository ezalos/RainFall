//gcc lvl5.c -o lvl5 -fno-stack-protector -z execstack

#include <stdio.h>
#include <stdlib.h>

void o(void)
{
	system("/bin/sh");
	_exit(1);
}

#define BUFF	0x200

void n(void)
{
	char data[BUFF];

	fgets(data, BUFF, stdin);
	printf(data);
	exit(1);
}

void main(void)
{
	n();
}
