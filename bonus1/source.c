// gcc -fno-stack-protector source.c -o source  -z execstack
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int ac, char **av)
{
    char		buf[40];
    int32_t		val;

    val = atoi(av[1]);
    if (val > 9)
		return (1);
    memcpy(buf, av[2], val * 4);
    if (val == 0x574f4c46)//1464814662
	{
    	execl("/bin/sh", "sh", (char*)0);
    }
    return (0);
}
