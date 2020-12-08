#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	p(char *dest, char *s)
{
    char	buff[0xffc];

    puts(s);
    read(0, &buff, 0x1000);
    *strchr(buff, '\n') = 0;
    strncpy(dest, buff, 0x14);
    return;
}

void	pp(char *dest)
{
	char	buf1[0x10];
	char	buf2[0x14];
	int		i;

	p(buf2, " - ");
	p(buf1, " - ");
	strcpy(dest, buf2);
	i = 0;
	while (dest[i])
		i++;
	dest[i] = ' ';
	dest[i + 1] = '\0';
	strcat(dest, buf1);
}

int main(void)
{
    char	buf[0x2a];

    pp(buf);
    puts(buf);
    return 0;
}

// gcc -fno-stack-protector source.c -o source