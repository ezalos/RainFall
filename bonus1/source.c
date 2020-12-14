#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>


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
    	execl("/bin/sh", "sh", 0);
    }
    return (0);
}
