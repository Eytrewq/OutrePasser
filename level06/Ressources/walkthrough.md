# Level 06

## Méthode sources

On remarque une fonction `auth` qui verifie que le login donné en entré soit au moins de taille 5 et inférieur ou égal à 31. 
Ensuite la fonction vérifie l'authentification en hashant le login et en le comparant au serial.
La fonction `auth` est protégée par un `ptrace` pour nous empecher d'utiliser gdb facilement.

Il nous suffit de recreer la fonction de hashage en C et d'obtenir le serial
pour un login donné. (voir source.c)

Ici: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
Serial: 6248749

```bash
level06@OverRide:~$ ./level06 
***********************************
*               level06           *
***********************************
-> Enter Login: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6248749         
Authenticated!
$ cat /home/users/level07/.pass
GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8
```

## Méthode GDB

On remarque une fonction `auth` qui verifie que le login donné en entré soit au moins de taille 5 et inférieur ou égal à 31.

```asm
...
0x08048786 <+62>:	cmpl   $0x5,-0xc(%ebp)
0x0804878a <+66>:	jg     0x8048796 <auth+78>
...
0x08048818 <+208>:	cmp    $0x1f,%al
0x0804881a <+210>:	jg     0x8048823 <auth+219>
```

La fonction `auth` est protégée par un `ptrace`. Nous pouvons contourner cette protection.
Nous trouvons l'endroit de la comparaison entre le hash et notre serial à l'aide de gdb.

```asm
0x08048866 <+286>:	cmp    -0x10(%ebp),%eax
0x08048869 <+289>:	je     0x8048872 <auth+298>
0x0804886b <+291>:	mov    $0x1,%eax
```

```bash
...
(gdb) catch syscall ptrace
Catchpoint 1 (syscall 'ptrace' [26])
(gdb) commands 1
Type commands for breakpoint(s) 1, one per line.
End with a line saying just "end".
>set ($eax) = 0
>continue
>end
(gdb) b *0x08048866
Breakpoint 2 at 0x8048866
(gdb) r
Starting program: /home/users/level06/level06 
***********************************
*		level06		  *
***********************************
-> Enter Login: getflag
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: a

Catchpoint 1 (call to syscall ptrace), 0xf7fdb435 in __kernel_vsyscall ()

Catchpoint 1 (returned from syscall ptrace), 0xf7fdb435 in __kernel_vsyscall ()

Breakpoint 2, 0x08048866 in auth ()
(gdb) x/x $ebp-0x10
0xffffd698:	0x005f1eaa
(gdb) x/d $ebp-0x10
0xffffd698:	6233770
```

Et voilà, nous trouvons le serial associé au mot `getflag`.

```bash
level06@OverRide:~$ ./level06 
***********************************
*		level06		  *
***********************************
-> Enter Login: getflag
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6233770
Authenticated!
$ cat /home/users/level07/.pass
GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8
```
