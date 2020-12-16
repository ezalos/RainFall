// gcc -fno-stack-protector source.cpp -o source -z execstack -lstdc++
#include <string.h>
#include <unistd.h>

class Nb;

int			operator+(Nb a, Nb b);
int			operator-(Nb a, Nb b);

// void		*g_fun_tab[2] = {&operator+, &operator-};

int	(*g_funtab[2])(Nb, Nb) = {&operator+, &operator-};


class Nb
{

	public:
		int		(**fun_tab)(Nb, Nb);
		char	buf[0x64];
		int		value;

		Nb(int a)
		{
			fun_tab = g_funtab;
	        value = a;
		}

		void	setAnnotation(char *str)
		{
			memcpy(buf, str, strlen(str));
		}
};

int		operator+(Nb a, Nb b)
{
	return (a.value + b.value);
}

int		operator-(Nb a, Nb b)
{
	return (a.value - b.value);
}

int		main(int ac, char **av)
{
	if (ac < 2)
		_exit(1);

	Nb	*a;
	Nb	*b;

	a = new Nb(5);
	b = new Nb(6);
	a->setAnnotation(av[1]);
	return (((b->fun_tab)[0])(*a, *b));
}
