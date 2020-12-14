# Level0

## Solution
 * There is one file in our home, ```level0```, belonging to ```level1``` user, with suid.
 * We run the program with gdb and we observe that:
	* the program applies ```atoi``` function to ```argv[1]``` and compares the return value to ```0x1a7``` (```423```):
		* if not equal, prints ```No !``` on the ```stderr``` and returns ```0```
		* if the argument is equal to ```0x1a7```, the program launches ```/bin/sh``` command thanks to ```execv``` function
 * As ```/bin/sh``` has been launched with ```level1``` user permissions, we can execute ```cd ../level1; cat .pass``` and get password to switch to ```level1```.

 ```sh
 level0@RainFall:~$ ./level0 423
$ cd ../level1 && cat .pass
1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
 ```
