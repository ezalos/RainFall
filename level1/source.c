// gcc source.c -fno-stack-protector

#include <stdio.h>
#include <stdlib.h>

void run()
{
	fwrite("Good... Wait what?\n", 0x13, 0x1, stdout);
	system("/bin/sh");
}

int main()
{
	char var[76];
	gets(var);
}
