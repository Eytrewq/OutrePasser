#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char a_user_name[256];

int verify_user_name(char *name)
{
    puts("verifying username....\n");
    return strncmp(name, "dat_wil", 7);
}

int verify_user_pass(char *pass)
{
    return strncmp(pass, "admin", 5);
}

int main(int argc, char **argv)
{
    char str[64] = {0};

    puts("********* ADMIN LOGIN PROMPT *********");

    printf("Enter Username: ");

    fgets(a_user_name, 256, stdin);

    if (verify_user_name(a_user_name) == 0)
    {
        puts("Enter Password: ");
        fgets(str, 100, stdin);
        verify_user_pass(str);
        puts("nope, incorrect password...\n");
    }
    else
        puts("nope, incorrect username...\n");

    return 1;
}
