#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int password;

    puts("***********************************");
    puts("* \t     -Level00 -\t\t  *");
    puts("***********************************");
    printf("Password:");

    scanf("%d", &password);

    if (password != 0x149c)
    {
        puts("\nInvalid Password!");
        return 1;
    }
    else
    {
        puts("\nAuthenticated!");
        system("/bin/sh");
        return 0;
    }
}