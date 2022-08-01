#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ptrace.h>

int main(int argc, char ** argv) {
    int pid = fork();
    char str[132];
    int truc = 0;

    if (pid == 0) {
        prctl(PR_SET_PDEATHSIG, 1);
        ptrace(0, 0, 0, 0);
        puts("Give me some shellcode, k");
        gets(str);
        return 0;
    }

    do {
        wait(&truc);

        if (ptrace(3, pid, 44, 0) == 11) {
            puts("no exec() for you");
            kill(pid, SIGKILL);
            return 0;
        }

    } while (truc != 0);

    puts("child is exiting...");

    return 0;
}
