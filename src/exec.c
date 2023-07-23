#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#include "exec.h"
#include "unistd.h"

void execute(char* command) {
    __pid_t pid = fork();
    if (pid < 0) {
        printf("fork() caused an error.");
        exit(1);
    } else if (pid == 0) {
        char* token = strtok(command, " ");
        char* cmd;
        strcpy(cmd, token);
        token = strtok(NULL, " ");
        execlp(cmd, cmd, token, (char *)NULL);
        perror("execlp");
    } else {
        int childStatus;
        wait(&childStatus);
    }
}