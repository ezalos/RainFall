# Level1

## Resolution
 * There is one file in our home, ```level1```, belonging to ```level2``` user, with suid.
 * Here's the hand-decompiled source code we propose for this binary: [source.c](source.c)

 * We run the program with gdb and we observe that:
	* `main()` makes use of `gets()` with an on stack array of size 0x40
	* There is an unused function nammed `run` at `0x08048444` which executes `system("/bin/sh")`

 * We have the appropriate setup for a Buffer-Overflow attack:
    * We want to modify the `POP EIP` instruction (or equivalently `RET` instruction).
		* It normally allows to continue the execution of the parent function
		* Here we instead want to execute the `run()` function
	* When `gets()` is called we want to write past through the buffer, here is the stack layout:
		* [gets arg :	64 octets] -> We can write any value here
		* [EBP:			8 octetcs] -> We would like to conserve this value so we avoid segfalut
		* [EIP:			8 octetcs] -> We want to change this value so it points to `run()`, it needs to be `0x08048444`
	
 * We now have to put all this theory in practice, keeping in mind the stack uses Big Endian

 1. Lets prepare our string for the Buffer-Overflow attack:
 ```sh
python -c "print('x' * 76 + '44840408'.decode('hex'))" > /var/crash/lvl1
 ```
 2. Now we want to use the content of lvl1 as stdin for gets,
 and then manually get access to stdin once `system("/bin/sh")` is executed.
 For this we can use cat, with `-` as a second argument, so once the file has been read,
 cat will transmit stdin :
 ```sh
 cat /var/crash/lvl1 - | ./level1
 ```

 3. We now are in the shell session, and we can simply cat the content `.pass` with: 
 ```
 cat /home/user/level2/.pass
 ```
