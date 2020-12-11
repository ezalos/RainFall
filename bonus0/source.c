#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	p(char *dest, char *s)
{
    char	buff[0x1000];

    puts(s);
    read(0, &buff, 0x1000);
    *strchr(buff, '\n') = 0;
    strncpy(dest, buff, 0x14);
    return;
}

void	pp(char *final_buf)
{
	char	buf1[0x14];
	char	buf2[0x14];
	size_t	i;

	p(buf2, " - ");
	p(buf1, " - ");
	strcpy(final_buf, buf2);
	i = strlen(final_buf);
	final_buf[i] = ' ';
	final_buf[i + 1] = '\0';
	strcat(final_buf, buf1);
}

int main(void)
{
    char	final_buf[0x2a];

    pp(final_buf);
    puts(final_buf);
    return (0);
}

// gcc -fno-stack-protector source.c -o source