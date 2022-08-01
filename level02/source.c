#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv) {
    
    char str[112] = {0}; 
    char data[48] = {0};
    char str2[112] = {0};

    FILE * file = fopen("/home/users/level03/.pass", "r"); 

    if (file == NULL) {
        fwrite("ERROR: failed to open password file\n", 1, 36, stdout);
        exit(1);
    }

    int len = fread(data, 1, 41, file); 
    data[strcspn(data, "\n")] = 0;

    if (len != 41) {
        fwrite("ERROR: failed to read password file\n", 1, 36, stdout);
        exit(1);
    }

    fclose(file);

    puts("===== [ Secure Access System v1.0 ] =====");
    puts("/***************************************\\");
    puts("| You must login to access this system. |");
    puts("\\**************************************/");

    printf("--[ Username: ");
    fgets(str, 100, stdin);
    str[strcspn(str, "\n")] = 0;

    printf("--[ Password: ");
    fgets(str2, 100, stdin);
    str2[strcspn(str2, "\n")] = 0;

    puts("*****************************************");

    if (strncmp(data, str2, 41) == 0) {
        
        printf("Greetings, %s!\n", str);
        system("/bin/sh");
        return 0;
    }
    
    printf(str);
    puts(" does not have access!");
    exit(1);
}
