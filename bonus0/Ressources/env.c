#include <stdio.h>

int		main(int ac, char **av)
{
	(void)ac;
	printf("%s: %p\n", av[1], getenv(av[1]));
	return (0);
}