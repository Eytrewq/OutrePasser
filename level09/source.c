#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void secret_backdoor()
{
    char str[128];
    fgets(str, 128, stdin);
    system(str);
}

void handle_msg()
{
    char mainbuffer[192];

    set_username(mainbuffer);
    set_msg(mainbuffer);
    puts(">: Msg sent!");
}

void set_msg(char *mainbuffer)
{
    char msgbuffer[1024];

    puts(">: Msg @Unix-Dude");
    printf(">>: ");
    fgets(msgbuffer, 1024, stdin);
    int n = *(int *)(mainbuffer + 180);
    strncpy(mainbuffer, msgbuffer, n);
}

void set_username(char *mainbuffer)
{
    char usernamebuffer[128];

    puts(">: Enter your username");
    printf(">>: ");

    fgets(usernamebuffer, 128, stdin);

    int i = 0;

    while (usernamebuffer[i])
    {
        mainbuffer[140 + i] = usernamebuffer[i];
        if (i > 40)
            break;
        i++;
    }

    printf(">: Welcome, %s", mainbuffer + 140);
}

int main(int argc, char **argv)
{
    puts("--------------------------------------------\n \
          |   ~Welcome to l33t-m$n ~    v1337        |\n \
          --------------------------------------------");
    handle_msg();
    return 0;
}
