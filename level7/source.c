#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

char	c[0x44];

void	m()
{
	int		tm;

	tm = time(NULL);
	printf("%s - %d\n", c, tm);
}

int		main(int ac, char **av)
{
	int		*m1;//esp + 0x1c
	int		*m3;//esp + 0x18


	m1 = malloc(0x8);//008
	*m1 = 0x1;

	m1[1] = malloc(0x8);//018

	m3 = malloc(0x8);//028
	*m3 = 0x2;

	m1[1] = malloc(0x8);//038 ?

	strcpy(m1[1], av[1]);

	strcpy(m3[1], av[2]);

	fgets(c, 0x44, fopen("/home/user/level8/.pass", "r"));

	puts("~~");
	return (0);
}
