#include <string.h>
#include <stdlib.h>
// #include <new>

using namespace std;
class Nb
{
	char	buf[0x64];
	int		value;

	public:
		Nb(int a)
		{
	        this ->value = a;
		}

        void *operator new(size_t size)
        {
            void *p = malloc(size); 
            return p;
        }
		void	operator+=(Nb a)
		{
			this ->value += a.value;
		}
		void	setAnnotation(char *str)
		{
			memcpy(this ->buf, str, strlen(str));
		}
};


// Nb operator+(Nb a, Nb b)
// {
// 	return (Nb(a.value + b.value));
// }

// void	Nb::operator+=(Nb a)
// {
// 	value += a.value;
// }

// void	*Nb::operator new(size_t stAllocateBlock, int val)
// {
// 	Nb	*a;
// 	a = (Nb*)malloc(stAllocateBlock);
// 	a->value = val;
// 	return (a);
// }

// void	Nb::setAnnotation(char *str)
// {
// 	memcpy(buf, str, strlen(str));
// }


int		main(int ac, char **av)
{
	Nb	*a = new Nb(5);
	Nb	*b = new Nb(6);

	a->setAnnotation(av[1]);
	*b += *a;
	return (0);
}
