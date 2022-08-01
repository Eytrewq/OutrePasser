#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int decrypt(int arg)
{
    if (arg != 18)
        puts("\nInvalid Password");
    else
        system("/bin/sh");

    return 18;
}

int test(int a, int b)
{
    switch (b - a)
    {
    case 1:
        return decrypt(1);
    case 2:
        return decrypt(2);
    case 3:
        return decrypt(3);
    case 4:
        return decrypt(4);
    case 5:
        return decrypt(5);
    case 6:
        return decrypt(6);
    case 7:
        return decrypt(7);
    case 8:
        return decrypt(8);
    case 9:
        return decrypt(9);
    case 16:
        return decrypt(16);
    case 17:
        return decrypt(17);
    case 18:
        return decrypt(18);
    case 19:
        return decrypt(19);
    case 20:
        return decrypt(20);
    case 21:
        return decrypt(21);
    default:
        return decrypt(rand());
    }
}

int main(int argc, char **argv)
{
    int password;

    srand(time(NULL));
    puts("***********************************");
    puts("*\t\tlevel03\t\t**");
    puts("***********************************");
    printf("Password:");
    scanf("%d", &password);
    test(password, 0x1337d00d);
    return 0;
}
