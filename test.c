#include <unistd.h>
#include <libc.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	char	str[1000];
	
	bzero(str, 1000);
	gets(str);
	printf("%s\n", str);
	//system(str);
	return (0);
}
