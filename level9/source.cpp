#include <string.h>
#include <stdlib.h>
#include <new>

class Nb
{
	public:
	char	buf[0x64];
	int		value;

	Nb(int);
	void	operator+=(Nb a);
	void	setAnnotation(char *str);

};


Nb::Nb(int val)
{
	value = val;
}

// Nb operator+(Nb a, Nb b)
// {
// 	return (Nb(a.value + b.value));
// }

void	Nb::operator+=(Nb a)
{
	value += a.value;
}

// void	*Nb::operator new(size_t stAllocateBlock, int val)
// {
// 	Nb	*a;
// 	a = (Nb*)malloc(stAllocateBlock);
// 	a->value = val;
// 	return (a);
// }

void	Nb::setAnnotation(char *str)
{
	memcpy(buf, str, strlen(str));
}


int		main(int ac, char **av)
{
	Nb	*a;
	Nb	*b;
	
	a = new Nb(5);
	b = new Nb(6);

	a->setAnnotation(av[1]);
	*b += *a;
	return (0);
}

