// gcc -fno-stack-protector source.c -o source  -z execstack

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

char	c[0x44];

void	m()
{

	printf("%s - %d\n", c, (int)time(NULL));
}

int		main(int ac, char **av)
{
	void	**m1;//esp + 0x1c
	void	**m3;//esp + 0x18

	m1 = malloc(0x8);//008
	m1[0] = (void*)0x1;

	m1[1] = malloc(0x8);//018

	m3 = malloc(0x8);//028
	m3[0] = (void*)0x2;

	m3[1] =  malloc(0x8);

	strcpy(m1[1], av[1]);

	strcpy(m3[1], av[2]);

	fgets(c, 0x44, fopen("/home/user/level8/.pass", "r"));

	puts("~~");
	return (0);
}
