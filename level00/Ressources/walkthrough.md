# Level 00

Un simple désassemblage du binaire nous permet d'obtenir le mot de passe: 5276

```asm
mov    0x1c(%esp),%eax
cmp    $0x149c,%eax <- 0x149c == 5276
jne    0x804850d <main+121>
```

Et c'est tout pour cet exercice d'introduction.

```bash
level00@OverRide:~$ ./level00 
***********************************
*            -Level00 -           *
***********************************
Password:5276

Authenticated!
$ cat /home/users/level01/.pass                   
uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL
```