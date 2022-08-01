#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int log_wrapper(FILE *file, char *truc, char *format)
{
    char str[256];
    int len = 0;

    strcpy(str, truc);

    while (str[len]) len++;

    snprintf(str + len, 256 - len, format);

    size_t s = strcspn(str, "\n");
    str[s] = 0;
    fprintf(file, "LOG: %s\n", str);
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s filename\n", argv[0]);
    }

    FILE *file = fopen("./backups/.log", "w");

    if (file == NULL)
    {
        printf("ERROR: Failed to open %s\n", "./backups/.log");
        exit(1);
    }

    char *filename = argv[1];
    log_wrapper(file, "Starting back up: ", filename);
    FILE *file2 = fopen(filename, "r");

    if (file2 == NULL)
    {
        printf("ERROR: Failed to open %s\n", filename);
        exit(1);
    }

    char file3name[] = "./backups/";

    strncat(file3name, filename, 100);

    int fd = open(file3name, O_EXCL|O_CREAT|O_WRONLY);// O_EXCL|O_CREAT|O_WRONLY == 193 

    if (fd < 0)
    {
        printf("ERROR: Failed to open %s%s\n", "./backups/", filename);
        exit(1);
    }

    char c = fgetc(file2);

    while (c != EOF)
    {
        write(fd, &c, 1);
        c = fgetc(file2);
    }

    log_wrapper(file, "Finished back up ", filename);
    fclose(file2);
    close(fd);
}
