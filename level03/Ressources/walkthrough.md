# Level 03

Nous remarquons une fonction `decrypt` et `test`.

La fonction `decrypt` est appellé à 22 reprise dans la fonction `test`,
chacune de ces occurences dépend des arguments passés. 
La fonction `decrypt` prend en argument un int, entre 1 et 21 inclus.

Nous tentons d'apeller la fonction avec gdb.

```
(gdb) r main
Starting program: /home/users/level03/level03 main
***********************************
*               level03         **
***********************************
Password:ffdfd

Invalid Password
[Inferior 1 (process 1810) exited normally]
(gdb) b main
Breakpoint 1 at 0x804885d
(gdb) r
Starting program: /home/users/level03/level03 main

Breakpoint 1, 0x0804885d in main ()
(gdb) p decrypt(1)

Invalid Password
$1 = 18
(gdb) p decrypt(2)

Invalid Password
$2 = 18
```

Nous remarquons que la valeur de retour de la fonction `decrypt` reste 18 malgré les différents arguments. Nous tentons donc intelligemment 18 comme entrée: Tadam !

```
(gdb) p decrypt(18)
$ echo lol
lol
```

Donc il nous suffirait que la fonction `decrypt` soit appelée avec l'argument 18 pour obtenir le term.

La fonction `test` est celle qui appelle `decrypt` dans le programme.
On observe que la valeur passée à `decrypt` est égale au second argument de `test` moins son premier argument:

```asm
 804874d:       8b 45 08                mov    0x8(%ebp),%eax <- premier argument
 8048750:       8b 55 0c                mov    0xc(%ebp),%edx <- deuxième argument
 8048753:       89 d1                   mov    %edx,%ecx
 8048755:       29 c1                   sub    %eax,%ecx
```

Donc avec `test(0, 18)` ou `test(2, 20)` cela devrait fonctionner et ouvrir un term.
Le password recupéré par le programme est parsé grâce à scanf puis passé à `test` avec une constante `0x1337d00d`.

Donc il nous suffit de mettre en password la constante - 18.

C'est à dire: `0x1337d00d - 18 = 322424827`

```bash
level03@OverRide:~$ ./level03 
***********************************
*               level03         **
***********************************
Password:322424827
$ cat /home/users/level04/.pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
```

