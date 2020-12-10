
int main(int ac, char **av)
{
    int32_t		ret;
    char		buf[40];
    int32_t		val;
    
    val = atoi(av[1]);
    if (val < 10)
	{
        memcpy(buf, av[2], val * 4);
        if (val == 0x574f4c46)//1464814662
		{
        	execl("/bin/sh", "sh", 0);
        }
        ret = 0;
    }
	else
	{
        ret = 1;
    }
    return (ret);
}

