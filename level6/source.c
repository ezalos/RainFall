#include <string.h>
#include <stdlib.h>

void	m(void)
{
	puts("Nope");
}

void	n(void)
{
	system("/bin/cat /home/user/level7/.pass");
}

void	main(int ac, char **av)
{
	void	*ptr1;
	void	(**ptr2)(void);

	ptr1 = malloc(0x40);
	ptr2 = malloc(0x4);
	*ptr2 = m;
	strcpy(ptr1, av[1]);
	(*ptr2)();
}

// gcc -fno-stack-protector source.c -o source  -z execstack
