#include <stdio.h>

int	main(void)
{
	int		i;
	printf("%08x%08x%08x%08x%n\n", &i);
	printf("%d\n", i);
	return (0);
}