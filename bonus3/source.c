// gcc -fno-stack-protector source.c -o source  -z execstack
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int ac, char **av)
{
	char	buf[0x84];
	FILE	*fd;

    fd = fopen("/home/user/end/.pass", "r");
	bzero(buf, 0x84);
    if (fd == 0 || ac != 0x2)
		return (-1);
	else
	{
        fread(buf, 1, 0x42, fd);
		buf[0x41] = 0;
		buf[atoi(av[1])] = 0;
        fread(buf + 0x42, 1, 0x41, fd);
        fclose(fd);
        if (strcmp(buf, av[1]) == 0)
            execl("/bin/sh", "sh", (char*)0);
		else
            puts(&buf[0x42]);
    }
	return (0);
}
