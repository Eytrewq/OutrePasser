#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{    
    char    str[100];
    int     i = 0;

    fgets(str, 100, stdin);
    
    while (str[i])
    {
        if (str[i] > 'A' && str[i] <= 'Z')
            str[i] += 32;
        i++;
    }
    
    printf(str);
    exit(0);
}
