// gcc source.c -fno-stack-protector -z execstack

#include <stdio.h>
#include <stdlib.h>

void run()
{
	fwrite("Good... Wait what?\n", 0x1, 0x13, stdout);
	system("/bin/sh");
}

int main()
{
	char	var[0x40];

	gets(var);
}
