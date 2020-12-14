# bonus3

## Solution
 * There is one file in our home, ```bonus3```, belonging to ```end``` user, with suid.
 * Here's the hand-decompiled source code we propose for this binary: [source.c](source.c)

## Explanation
Keeping only the parts which matters:
 * The program calls `fopen("/home/user/end/.pass", "r")`
 * It then does a read on it : `fread(buf, 1, 0x42, fd)`
 * `av[1]` is passed to `atoi()` and is used to put the `\0` to the buffer
 * Finally if `(strcmp(buf, av[1]) == 0)` we get access to `execl`

## Execution
We can launch the program this way:
```sh
./bonus3 ""
```

Because this way `strcmp()` will effectively return that the 2 strings are equals (as `atoi()` understand this input as `0`)
