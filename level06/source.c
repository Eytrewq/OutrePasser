#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int auth(char *login, int serial)
{
    int len = strnlen(login, 32);

    if (len <= 5 || len > 31)
        return 1;

    if (ptrace(login) == -1) {
        puts("\e[32m----------------------------");
        puts("\e[31m| !! TAMPERING DETECTED !! |"); 
        puts("\e[32m----------------------------");
        return 1;
    }

    int i = 0;
    int hash = (login[3] ^ 0x1337) + 0x5eeded;

    while (i < len)
    {
        hash = (hash ^ login[i]) % 1337 + hash;
        i++;
    }

    return hash != serial;
}

int main(int argc, char **argv)
{
    char login[32];
    int serial;

    puts("***********************************");
    puts("*\t\tlevel06\t\t  *");
    puts("***********************************");
    printf("-> Enter Login: ");

    fgets(login, 32, stdin);

    puts("***********************************");
    puts("***** NEW ACCOUNT DETECTED ********");
    puts("***********************************");
    printf("-> Enter Serial: ");

    scanf("%u", &serial);

    if (auth(login, serial) == 0)
    {
        puts("Authenticated!");
        system("/bin/sh");
    }

    return 0;
}