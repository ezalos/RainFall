//gcc lvl3.c -o lvl3 -fno-stack-protector -z execstack

#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE (0x200)// == 512

void v(void)
{
	static int	m;
	char		data[BUFFER_SIZE];

	fgets(data, BUFFER_SIZE, stdin);
	printf(data);
	if (m == 0x40)
	{
		fwrite("Wait what?!\n", 0x1, 0xc, stdout);
		system("/bin/sh");
	}
}

int main(void)
{
	v();
}
