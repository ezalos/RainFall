#include <stdio.h>
#include <stdlib.h>

char *run_fwrite = "Wait what";

char *run_system = "/bin/sh";
//   0x08048444 <+0>:	push   ebp
//   0x08048445 <+1>:	mov    ebp,esp
void run()
{
//   0x08048447 <+3>:	sub    esp,0x18
	char var[0x18];

   //0x0804844a <+6>:	mov    eax,ds:0x80497c0
   //0x0804844f <+11>:	mov    edx,eax
   //0x08048451 <+13>:	mov    eax,0x8048570
   //0x08048456 <+18>:	mov    DWORD PTR [esp+0xc],edx
   //0x0804845a <+22>:	mov    DWORD PTR [esp+0x8],0x13
   //0x08048462 <+30>:	mov    DWORD PTR [esp+0x4],0x1
   //0x0804846a <+38>:	mov    DWORD PTR [esp],eax
   //0x0804846d <+41>:	call   0x8048350 <fwrite@plt>
   fwrite(run_fwrite, 10, 1, ?);
   //size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

   //0x08048472 <+46>:	mov    DWORD PTR [esp],0x8048584
   //0x08048479 <+53>:	call   0x8048360 <system@plt>
	system(run_system);

   //0x0804847e <+58>:	leave  
   //0x0804847f <+59>:	ret
   return ;

}



//0x08048480 <+0>:	push   ebp
//0x08048481 <+1>:	mov    ebp,esp
int main()
{
//0x08048483 <+3>:	and    esp,0xfffffff0
//0x08048486 <+6>:	sub    esp,0x50
	char var[0x40];
//0x08048489 <+9>:	lea    eax,[esp+0x10]
//0x0804848d <+13>:	mov    DWORD PTR [esp],eax
//0x08048490 <+16>:	call   0x8048340 <gets@plt>
	gets(var);
//0x08048495 <+21>:	leave  
//0x08048496 <+22>:	ret   
	return /*gets()*/0;
}
