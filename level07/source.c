#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void            clear_stdin()
{
    char c = getchar();
    while ((c != '\n') == (c != EOF))
        c = getchar();
}

unsigned        get_unum()
{
    unsigned result = 0;
    fflush(stdout);
    scanf("%u", &result);
    clear_stdin();
    return result;
}

int store_number(unsigned *tab) {
    printf(" Number: ");
    unsigned number = get_unum();
    printf(" Index: ");
    unsigned index = get_unum();
    if ((index % 3 == 0) || (number & -0x1000000) == -0x49000000)
    {
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil!");
        puts(" *** ERROR! ***");
        return 1;
    }
    *(4 * index + tab) = number;
    return 0;
}

int read_number(unsigned *tab) {
    printf(" Index: ");
    unsigned index = get_unum();
    printf(" Number at data[%u] is %u\n", index, *(4 * index + tab));
    return 0;
}

int main(int argc, char **argv, char **env) {
    unsigned tab[100];
    char str[20];
    int ret;

    while(*argv)
    {
        memset(*argv, 0, strlen(*argv));
        argv++;
    }

    while(*env)
    {
        memset(*env, 0, strlen(*env));
        env++;
    }

    puts("----------------------------------------------------\n \
            Welcome to wil's crappy number storage service!   \n \
          ----------------------------------------------------\n \
           Commands:                                          \n \
              store - store a number into the data storage    \n \
              read  - read a number from the data storage     \n \
              quit  - exit the program                        \n \
          ----------------------------------------------------\n \
             wil has reserved some storage :>                 \n \
          ----------------------------------------------------\n");

    while (1) {
        ret = 1;
        printf("Input command: ");
        fgets(str, 20, stdin);
        if (str == "read")
            ret = read_number(tab);
        else if(str == "store")
            ret = store_number(tab);
        else if (str == "quit")
            return (0);

        if (ret == 0)
            printf(" Completed %s command successfully\n", str);
        else
            printf(" Failed to do %s command\n", str);
    }
}
